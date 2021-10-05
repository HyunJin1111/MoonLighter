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
	// 이미지 파일에서 그림을 읽어서 저장할 객체
	ID2D1Bitmap *mp_bitmap;
	// Gaussian Blur 효과의 현재 값 (5에서 시작해서 점차적으로 줄어듬)
	float m_step;
	// Gaussian Blur 효과를 사용하기 위한 객체
	ComPtr<ID2D1Effect> m_gaussian_blur_effect;
public:
	MyWnd()
	{
		mp_bitmap = NULL;
		m_step = 5.0f;   // Gaussian Blur 효과의 시작 값
	}

	virtual int OnCreate(CREATESTRUCT *ap_create_info)
	{
		TW_Wnd::OnCreate(ap_create_info);

		// tips_yjin.png 파일을 읽어서 gp_bitmap 객체에 이미지를 생성한다.
		if (1 == TWAPI_LoadImage(mp_dc, &mp_bitmap, L"tips_yjin.png")) {
			// Gaussian Blur 효과를 사용하기 위한 객체를 생성한다.
			mp_dc->CreateEffect(CLSID_D2D1GaussianBlur, &m_gaussian_blur_effect);
			// 현재 읽은 그림을 Gaussian Blur를 적용하기 위한 기본 이미지로 설정한다.
			m_gaussian_blur_effect->SetInput(0, mp_bitmap);
			// 0.1초마다 화면을 갱신하도록 타이머를 설정한다.
			SetTimer(1, 100);
		}
		return 0;
	}

	virtual void OnPaint()
	{
		// Direct2D의 Device Context를 사용해서 그림 그리기를 시작한다.
		mp_dc->BeginDraw();

		// Gaussian Blur 효과가 적용된 이미지를 화면에 출력한다.
		if (mp_bitmap != NULL) mp_dc->DrawImage(m_gaussian_blur_effect.Get());

		mp_dc->EndDraw();
		// DC에 그려진 그림을 화면에 출력한다.
		mp_sc->Present1(1, 0, &m_sc_parameters);
	}

	virtual void OnTimer(UINT a_timer_id)
	{
		if (a_timer_id == 1) {  // 0.1초마다 발생하는 타이머인지 체크한다.
			// m_step 값이 0에 가까워질수록 m_step의 값이 천천히 줄어들도록 한다.
			// m_step 값이 0이면 Gaussian Blur 효과가 적용되지 않는다.
			m_step = m_step - 0.5f / (10.0f / m_step);
			if (m_step < 0.1) { // m_step 값이 0이 되면 
				// Gaussian Blur 효과의 적용 값을 0으로 적용시켜서 효과가 미적용된 그림을 보여준다.
				m_gaussian_blur_effect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, 0.0f);
				if (m_step <= 0.05) m_step = 5.0f;  // 다시 Gaussian Blur 효과를 적용한다.
			}
			else {
				// m_step 값을 기준으로 Gaussian Blur 효과를 적용한다.
				m_gaussian_blur_effect->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, m_step);
			}
			Invalidate(); // 화면을 무효화 시켜서 WM_PAINT 메시지를 발생시킨다.
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