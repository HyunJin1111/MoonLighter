#pragma once
#include "singletonBase.h"

class dtdManager : public singletonBase<dtdManager>
{
public:
	static dtdManager* GetInstance()
	{
		static dtdManager instance;
		return &instance;
	}
	enum class DefaultBrush : UINT
	{
		White = 0, Black, Yellow, Red, Blue, Green, Gray, Purple, End
	};
private:
	//Factory, RenderTarget
	ID2D1Factory			*_dFactory;
	ID2D1HwndRenderTarget	*_dRenderTarget;
	ID2D1BitmapRenderTarget	*_dBitRenderTarget;
	ID2D1Bitmap				*_dBitmap;

	//Brush
	ID2D1BitmapBrush		*_dBitmapBrush;
	ID2D1SolidColorBrush	*_dBrush;

	//Text
	IDWriteFactory			*_dWFactory;
	IDWriteTextFormat		*_dWFormat;
	//색상 추가를 위한 브러쉬
	ID2D1SolidColorBrush* mDefaultBrushList[((UINT)DefaultBrush::End)];
	//맵에 색상추가!
	typedef map<wstring, IDWriteTextFormat*>::iterator TextIter;
	map<wstring, IDWriteTextFormat*> mFontList;
	//Camera
	HRESULT hr;

	float _sizeX;
	float _sizeY;

	bool _clear;

public:
	HRESULT init();
	void release();
	void render();
	void render(RECT rc);

	void beginDraw();
	void endDraw();
	
	void Rectangle(D2D1_RECT_F rc);
	void Rectangle(RECT rc );
	void Rectangle(float left, float top, float right, float bottom);
	void printText(LPCWCHAR text, float x, float y, float width, float height);
	void printText(LPCWCHAR text, D2D1_RECT_F rc);

	void setBackBuffer(float width, float height);

	void setRotation(float angle, float x, float y);
	void setScale(float x, float y);
	void resetRotation();
	void resetWindowSize(UINT width, UINT height);
	void sizeUP() { _sizeX += 0.01; _sizeY += 0.01; }
	void sizeDOWN() { _sizeX -= 0.01; _sizeY -= 0.01; }
	void resetSize() { _sizeX = 1.0; _sizeY = 1.0; }
	//색상 추가
	void CreateDefaultBrush();
	//글꼴 추가
	void AddTextFormat(const wstring& font, const float& defaultSize = 1.f);
	//라인 출력
	void DrawLine(const POINT& start, const POINT& end, const D2D1::ColorF::Enum& color, const float alpha,	const float strokeWidth = 1.f);
	void DrawLine(const POINT& start, const POINT& end, const DefaultBrush& defaultBrush = DefaultBrush::Black,	const float strokeWidth = 1.f);
	//텍스트 출력(기본 브러쉬 사용) 
	void RenderText(const int x, const int y, const wstring& text, const int size,
		const DefaultBrush& defaultBrush = DefaultBrush::Black,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"돋움");
	//텍스트 출력 (원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void RenderText(const int x, const int y, const wstring& text, const COLORREF& color, const float alpha, const int size,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"돋움");
	//텍스트 필드 출력 (기본 브러쉬 사용) 
	void RenderTextField(const int x, const int y, const wstring& text, const int size, const int width, const int height,
		const DefaultBrush& defaultBrush = DefaultBrush::Black,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"돋움");
	//텍스트 필드 출력(원하는 색상과 알파값으로 브러쉬 생성해서 출력)
	void RenderTextField(const int x, const int y, const wstring& text, const COLORREF& color,
		const int size, const int width, const int height,
		const float alpha = 1.0f,
		const DWRITE_TEXT_ALIGNMENT& align = DWRITE_TEXT_ALIGNMENT_LEADING,
		const wstring& font = L"돋움");
	void DrawRectangle(const RECT& rc, const D2D1::ColorF::Enum& color, const float alpha,
		const float strokeWidth = 1.f);
	void DrawRectangle(const RECT& rc, const DefaultBrush& defaultBrush = DefaultBrush::Black,
		const float strokeWidth = 1.f, const float angle = 0);
	void FillRectangle(const RECT& rc, const  D2D1::ColorF::Enum& color, const float alpha);
	void FillRectangle(const RECT& rc, const DefaultBrush& defaultBrush = DefaultBrush::Black, float angle = 0.f);

	void DrawEllipse(const int x, const int y, const float radius, const D2D1::ColorF color, const float alpha = 1.f,
		const float strokeWidth = 1.f);
	void DrawEllipse(const D2D1_POINT_2F& point, const float radius, const D2D1::ColorF color, const float alpha = 1.f,
		const float strokeWidth = 1.f);
	void FillEllipse(const int x, const int y, const float radius, const  D2D1::ColorF  color, const float alpha = 1.f);
	void FillEllipse(const D2D1_POINT_2F& point, const float radius, const  D2D1::ColorF  color, const float alpha = 1.f);


	//======================================
	D2D1_COLOR_F getBrushColor() { return _dBrush->GetColor(); }
	void setBrushColor(D2D1_COLOR_F color) { _dBrush->SetColor(color); }



	ID2D1HwndRenderTarget* getRenderTarget() { return _dRenderTarget; }
	ID2D1BitmapRenderTarget* getBitRenderTarget() { return _dBitRenderTarget; }

	void setClear(bool clear) { _clear = clear; }
	bool getClear() { return _clear; }
};
#define D2DDEFAULTBRUSH dtdManager::DefaultBrush
#define D2D1COLOR D2D1::ColorF
