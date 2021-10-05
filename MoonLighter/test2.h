#include "stdafx.h"
#include "test2.h"
#include "twapi_w01.h"

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "dxguid.lib")

#ifdef _DEBUG 
#pragma comment(lib, "DSH_TWAPI_W01.lib") 
#else
#pragma comment(lib, "RST_TWAPI_W01.lib") 
#endif

class MyWnd : public TW_Wnd
{
protected:
	// �̹��� ���Ͽ��� �׸��� �о ������ ��ü
	ID2D1Bitmap *mp_bitmap;
	// Gaussian Blur ȿ���� ���� �� (5���� �����ؼ� ���������� �پ��)
	float m_step;
	// Gaussian Blur ȿ���� ����ϱ� ���� ��ü
	ComPtr<ID2D1Effect> m_gaussian_blur_effect;
public:
	MyWnd()
	{
		mp_bitmap = NULL;
		m_step = 5.0f;   // Gaussian Blur ȿ���� ���� ��
	}

	virtual int OnCreate(CREATESTRUCT *ap_create_info)
	{
		TW_Wnd::OnCreate(ap_create_info);

		// tips_yjin.png ������ �о gp_bitmap ��ü�� �̹����� �����Ѵ�.
		if (1 == TWAPI_LoadImage(mp_dc, &mp_bitmap, L"tips_yjin.png")) {
			// Gaussian Blur ȿ���� ����ϱ� ���� ��ü�� �����Ѵ�.
			mp_dc->CreateEffect(CLSID_D2D1GaussianBlur, &m_gaussian_blur_effect);
			// ���� ���� �׸��� Gaussian Blur�� �����ϱ� ���� �⺻ �̹����� �����Ѵ�.
			m_gaussian_blur_effect->SetInput(0, mp_bitmap);
			// 0.1�ʸ��� ȭ���� �����ϵ��� Ÿ�̸Ӹ� �����Ѵ�.
			SetTimer(1, 100);
		}
		return 0;
	}

	virtual void OnPaint()
	{
		// Direct2D�� Device Context�� ����ؼ� �׸� �׸��⸦ �����Ѵ�.
		mp_dc->BeginDraw();

		// Gaussian Blur ȿ���� ����� �̹����� ȭ�鿡 ����Ѵ�.
		if (mp_bitmap != NULL) mp_dc->DrawImage(m_gaussian_blur_effect.Get());

		mp_dc->EndDraw();
		// DC�� �׷��� �׸��� ȭ�鿡 ����Ѵ�.
		mp_sc->Present1(1, 0, &m_sc_parameters);
	}

	virtual void OnTimer(UINT a_timer_id)
	{
		if (a_timer_id == 1) {  // 0.1�ʸ��� �߻��ϴ� Ÿ�̸����� üũ�Ѵ�.
			// m_step ���� 0�� ����������� m_step�� ���� õõ�� �پ�鵵�� �Ѵ�.
			// m_step ���� 0�̸� Gaussian Blur ȿ���� ������� �ʴ´�.
			m_step = m_step - 0.5f / (10.0f / m_step);
			if (m_step < 0.1) { // m_step ���� 0�� �Ǹ� 
				// Gaussian Blur ȿ���� ���� ���� 0���� ������Ѽ� ȿ���� ������� �׸��� �����ش�.
				m_gaussian_blur_effect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 0.0f);
				if (m_step <= 0.05) m_step = 5.0f;  // �ٽ� Gaussian Blur ȿ���� �����Ѵ�.
			}
			else {
				// m_step ���� �������� Gaussian Blur ȿ���� �����Ѵ�.
				m_gaussian_blur_effect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, m_step);
			}
			Invalidate(); // ȭ���� ��ȿȭ ���Ѽ� WM_PAINT �޽����� �߻���Ų��.
		}
	}

	virtual void OnDestroy()
	{
		TW_Wnd::OnDestroy();
		KillTimer(1);
		TW_IRelease(&mp_bitmap);
	}
};

class MyApp : public TW_WinApp
{
public:
	MyApp(HINSTANCE ah_instance, const wchar_t *ap_class_name)
		: TW_WinApp(ah_instance, ap_class_name, 1) { }

	virtual void InitInstance()
	{
		mp_wnd = new MyWnd;
		mp_wnd->Create(L"www.tipssoft.com - Gaussian blur Effect", 200, 200, 672, 504);
		mp_wnd->ShowWindow();
		mp_wnd->UpdateWindow();
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MyApp tips_app(hInstance, L"tipssoft");
	return tips_app.NormalProcess();
}