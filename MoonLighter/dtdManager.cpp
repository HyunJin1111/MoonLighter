#include "stdafx.h"
#include "D2DMANAGER.h"


HRESULT dtdManager::init()
{
	_dFactory = nullptr;
	_dRenderTarget = nullptr;
	_dBitRenderTarget = nullptr;
	_dBitmap = nullptr;
	_dBrush = nullptr;

	_dWFactory = nullptr;
	_dWFormat = nullptr;

	_clear = true;
	

	//Fafctory 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_dFactory);
	//int x1 = GetSystemMetrics(SM_CXSCREEN);
	//int x2 = GetSystemMetrics(SM_CYSCREEN);
	//Factory가 생성되었으면 RenderTarget 생성
	if (SUCCEEDED(hr)) {
		hr = _dFactory->CreateHwndRenderTarget(RenderTargetProperties(),
			HwndRenderTargetProperties(_hWnd, SizeU(WINSIZEX, WINSIZEY)),
			&_dRenderTarget);

	}
	CreateDefaultBrush();
	////RenderTarget과 호환되는 또 다른 RenderTarget(=BackBuffer) 생성
	//if (SUCCEEDED(hr)) {
	//	hr = _dRenderTarget->CreateCompatibleRenderTarget(SizeF(WINSIZEX * 2, WINSIZEY * 2),
	//		SizeU(WINSIZEX * 2, WINSIZEY * 2),
	//		&_dBitRenderTarget
	//	);
	//}

	//RenderTarget이 생성되었으면 Brush 생성
	if (SUCCEEDED(hr)) {
		hr = _dRenderTarget->CreateSolidColorBrush(ColorF(ColorF::White), &_dBrush);
	}

	//Brush가 생성되었으면 Text Factory 생성
	if (SUCCEEDED(hr)) {
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&_dWFactory)
		);
	}

	//Text Factory가 생성되었으면 Text Format 생성
	if (SUCCEEDED(hr)) {
		hr = _dWFactory->CreateTextFormat(
			L"돋움",
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.0f,
			L"ko-kr",
			&_dWFormat
		);
		mFontList.insert(make_pair(L"돋움", _dWFormat));
	}

	
	//wincodec(이미지 로더)을 사용하기 위함
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);


	

	return S_OK;
}

void dtdManager::release()
{
	TextIter iter = mFontList.begin();
	for (; iter != mFontList.end(); ++iter)
		NEW_SAFE_RELEASE(iter->second);

	for (UINT i = 0; i < (UINT)DefaultBrush::End; ++i)
		NEW_SAFE_RELEASE(mDefaultBrushList[i]);
	//동적 할당한 객체들 모두 해제
	SAFE_RELEASE2(_dFactory);
	SAFE_RELEASE2(_dRenderTarget);
	SAFE_RELEASE2(_dBrush);
	SAFE_RELEASE2(_dWFactory);

	
}

void dtdManager::render()
{
	if (!_dRenderTarget) return;

	_dRenderTarget->BeginDraw();
	_dRenderTarget->Clear(ColorF(ColorF::Black));

	/*SAFE_RELEASE2(_dBitmapBrush);
	_dRenderTarget->CreateBitmapBrush(_dBitmap,
		BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP),
		&_dBitmapBrush);
	D2D1_RECT_F rc = dRectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	_dRenderTarget->FillRectangle(rc, _dBitmapBrush);*/

	RECT screen = CAMERAMANAGER->getScreen();
	D2D1_RECT_F dest = { 0, 0, WINSIZEX, WINSIZEY };
	D2D1_RECT_F sour = { screen.left, screen.top, screen.right, screen.bottom };

	D2DMANAGER->getBitRenderTarget()->GetBitmap(&_dBitmap);

	if (_dRenderTarget) {
		_dRenderTarget->DrawBitmap(_dBitmap, dest,
			1.0, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sour);
	}

	_dRenderTarget->EndDraw();
}

void dtdManager::render(RECT rc)
{
	_dRenderTarget->BeginDraw();
	_dRenderTarget->Clear(ColorF(ColorF::Black));

	//_dRenderTarget->DrawRectangle(rc);

	_dRenderTarget->EndDraw();
}

void dtdManager::beginDraw()
{
	if (_dBitRenderTarget) {
		_dBitRenderTarget->BeginDraw();
		_dBitRenderTarget->Clear();
	}
}

void dtdManager::endDraw()
{
	if (_dBitRenderTarget) {

		_dBitRenderTarget->GetBitmap(&_dBitmap);

		_dBitRenderTarget->EndDraw();
	}
}

void dtdManager::Rectangle(D2D1_RECT_F rc)
{
	if (_dBitRenderTarget)
		_dBitRenderTarget->DrawRectangle(rc, _dBrush);
}

void dtdManager::Rectangle(float left, float top, float right, float bottom)
{

	D2D1_RECT_F d2dRC = { left, top,right,bottom };
	//D2D1_POINT_2F pt = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };

	if (_dBitRenderTarget)
		_dBitRenderTarget->DrawRectangle(d2dRC, _dBrush);
	//_dBitRenderTarget->FillRectangle(d2dRC, _dBrush);


}
void dtdManager::Rectangle(RECT rc)
{

	D2D1_RECT_F d2dRC = { rc.left, rc.top, rc.right, rc.bottom };
	D2D1_POINT_2F pt = { (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };

	if (_dBitRenderTarget)
	//	_dBitRenderTarget->DrawRectangle(d2dRC, _dBrush);
	_dBitRenderTarget->FillRectangle(d2dRC, _dBrush);
	//_dBitRenderTarget->FillRectangle(d2dRC, _dBrush);


}



void dtdManager::printText(LPCWCHAR text, float x, float y, float width, float height)
{
	_dBitRenderTarget->DrawTextA(text, lstrlenW(text), _dWFormat, dRectMakeCenter(x, y, width, height), _dBrush);
}

void dtdManager::printText(LPCWCHAR text, D2D1_RECT_F rc)
{
	_dBitRenderTarget->DrawTextA(text, lstrlenW(text), _dWFormat, rc, _dBrush);
}

void dtdManager::setBackBuffer(float width, float height)
{
	SAFE_RELEASE2(_dBitRenderTarget);

	if (_dRenderTarget) {
		_dRenderTarget->CreateCompatibleRenderTarget(SizeF(width, height), &_dBitRenderTarget);
	}
}

void dtdManager::setRotation(float angle, float x, float y)
{
	D2D1_POINT_2F pt = { x, y };
	_dBitRenderTarget->SetTransform(Matrix3x2F::Rotation(angle, pt));
}

void dtdManager::setScale(float x, float y)
{
	D2D1_POINT_2F pt = { x, y };
	_dBitRenderTarget->SetTransform(Matrix3x2F::Scale(D2D1::Size(-1.0f, 1.0f), pt));
}

void dtdManager::resetRotation()
{
	_dBitRenderTarget->SetTransform(Matrix3x2F::Identity());

}

void dtdManager::resetWindowSize(UINT width, UINT height)
{
	if (_dRenderTarget)
	{
		D2D1_SIZE_U size;
		size.width = width;
		size.height = height;
		_dRenderTarget->Resize(size);
		
		WinsizeX = size.width;
		WinsizeY = size.height;

	}
}
//색상 추가
void dtdManager::CreateDefaultBrush()
{
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Black]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::White]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Yellow]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Red]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Blue]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Green]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Gray]);
	_dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Purple, 1.0f), &mDefaultBrushList[(UINT)DefaultBrush::Purple]);
}
//글꼴 추가
void dtdManager::AddTextFormat(const wstring & font, const float & defaultSize)
{
	HRESULT hr;
	IDWriteTextFormat* format = NULL;

	hr = _dWFactory->CreateTextFormat(
		font.c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		defaultSize,
		L"ko",
		&format
	);

	mFontList.insert(make_pair(font, format));
}
void dtdManager::DrawLine(const POINT& start, const POINT& end, const DefaultBrush& defaultBrush, const float strokeWidth)
{
	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	POINT startPos = start;
	POINT endPos = end;

	_dBitRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y),
		D2D1::Point2F(endPos.x, endPos.y), mDefaultBrushList[(UINT)defaultBrush], strokeWidth);

}
void dtdManager::DrawLine(const POINT& start, const POINT& end, const D2D1::ColorF::Enum& color,
	const float alpha, const float strokeWidth)
{
	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	POINT startPos = start;
	POINT endPos = end;

	_dBitRenderTarget->DrawLine(D2D1::Point2F(startPos.x, startPos.y), D2D1::Point2F(endPos.x, endPos.y), brush, strokeWidth);
	NEW_SAFE_RELEASE(brush);
}
//기본 정의해둔 브러쉬로 텍스트 렌더링
void dtdManager::RenderText(const int x, const int y, const wstring & text, const int size, const DefaultBrush & defaultBrush, const DWRITE_TEXT_ALIGNMENT & align, const wstring & font)
{
	POINT pos;
	pos.x = x;
	pos.y = y;

	IDWriteTextLayout* layout = nullptr;
	HRESULT hr = _dWFactory->CreateTextLayout
	(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)text.length() * size,
		(float)size,
		&layout
	);
	assert(SUCCEEDED(hr));

	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();

	layout->SetFontSize((float)size, range);
	layout->SetTextAlignment(align);

	_dBitRenderTarget->SetTransform(Matrix3x2F::Identity());

	_dBitRenderTarget->DrawTextLayout(Point2F(pos.x, pos.y), layout,	mDefaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}
//새로운 브러쉬 생성후 렌더링
void dtdManager::RenderText(const int x, const int y, const wstring & text, const COLORREF & color, const float alpha, const int size, const DWRITE_TEXT_ALIGNMENT & align, const wstring & font)
{
	POINT pos;
	pos.x = x;
	pos.y = y;

	IDWriteTextLayout* layout = nullptr;
	//텍스트 레이아웃 생성
	_dWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)text.length() * size,
		(float)size,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);
	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_dBitRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, brush);

	NEW_SAFE_RELEASE(brush);
	NEW_SAFE_RELEASE(layout);
}
//영역내에서 기본 브러쉬로 글자 출력
void dtdManager::RenderTextField(const int x, const int y, const wstring & text, const int size, const int width, const int height, const DefaultBrush & defaultBrush, const DWRITE_TEXT_ALIGNMENT & align, const wstring & font)
{
	POINT pos;
	pos.x = x;
	pos.y = y;

	IDWriteTextLayout* layout = nullptr;
	_dWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_dBitRenderTarget->DrawTextLayout(D2D1::Point2F(pos.x, pos.y), layout, mDefaultBrushList[(UINT)defaultBrush]);

	NEW_SAFE_RELEASE(layout);
}
//영역안에서 새로운 브러쉬를 생성해서 폰트출력
void dtdManager::RenderTextField(const int x, const int y, const wstring & text, const COLORREF & color, const int size, const int width, const int height, const float alpha, const DWRITE_TEXT_ALIGNMENT & align, const wstring & font)
{
	POINT pos;
	pos.x = x;
	pos.y = y;

	IDWriteTextLayout* layout = nullptr;
	_dWFactory->CreateTextLayout(
		text.c_str(),
		text.length(),
		mFontList[font],
		(float)width,
		(float)height,
		&layout
	);

	//레이아웃 셋업
	DWRITE_TEXT_RANGE range;
	range.startPosition = 0;
	range.length = text.length();
	layout->SetFontSize((float)size, range);

	layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	layout->SetTextAlignment(align);

	//브러쉬 생성
	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_dBitRenderTarget->DrawTextLayout(D2D1::Point2F((float)x, (float)y), layout, brush);

	NEW_SAFE_RELEASE(layout);
	NEW_SAFE_RELEASE(brush);
}

void dtdManager::DrawRectangle(const RECT & rc, const D2D1::ColorF::Enum & color, const float alpha, const float strokeWidth)
{
	RECT rect = rc;

	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_dBitRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		brush, strokeWidth);

	NEW_SAFE_RELEASE(brush);
}

void dtdManager::DrawRectangle(const RECT & rc, const DefaultBrush & defaultBrush, const float strokeWidth, const float angle)
{
	RECT rect = rc;

	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(rc.left, rc.top));

	_dBitRenderTarget->SetTransform(rotateMatrix);

	_dBitRenderTarget->DrawRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		mDefaultBrushList[(UINT)defaultBrush], strokeWidth);
}

void dtdManager::FillRectangle(const RECT & rc, const D2D1::ColorF::Enum & color, const float alpha)
{
	RECT rect = rc;

	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color, alpha), &brush);
	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	_dBitRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom), brush);

	NEW_SAFE_RELEASE(brush);
}

void dtdManager::FillRectangle(const RECT & rc, const DefaultBrush & defaultBrush, float angle)
{
	RECT rect = rc;

	_dBitRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	D2D1::Matrix3x2F rotateMatrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(rc.left, rc.top));

	_dBitRenderTarget->SetTransform(rotateMatrix);

	_dBitRenderTarget->FillRectangle(D2D1::RectF((float)rect.left, (float)rect.top, (float)rect.right, (float)rect.bottom),
		mDefaultBrushList[(UINT)defaultBrush]);
}

void dtdManager::DrawEllipse(const int x, const int y, const float radius, const D2D1::ColorF color, const float alpha, const float strokeWidth)
{
	D2D1_POINT_2F point = D2D1::Point2F(x, y);

	D2D1_ELLIPSE el = D2D1::Ellipse(point, radius, radius);

	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(color, &brush);

	_dBitRenderTarget->DrawEllipse(el, brush);

	NEW_SAFE_RELEASE(brush);
}

void dtdManager::DrawEllipse(const D2D1_POINT_2F & point, const float radius, const D2D1::ColorF color, const float alpha, const float strokeWidth)
{
	D2D1_ELLIPSE el = D2D1::Ellipse(point, radius, radius);
	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(color, &brush);

	_dBitRenderTarget->DrawEllipse(el, brush);

	NEW_SAFE_RELEASE(brush);
}

void dtdManager::FillEllipse(const int x, const int y, const float radius, const D2D1::ColorF color, const float alpha)
{
	D2D1_POINT_2F point = D2D1::Point2F(x, y);

	D2D1_ELLIPSE el = D2D1::Ellipse(point, radius, radius);

	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(color, &brush);

	_dBitRenderTarget->FillEllipse(el, brush);

	NEW_SAFE_RELEASE(brush);
}

void dtdManager::FillEllipse(const D2D1_POINT_2F & point, const float radius, const D2D1::ColorF color, const float alpha)
{
	D2D1_ELLIPSE el = D2D1::Ellipse(point, radius, radius);

	ID2D1SolidColorBrush* brush;
	_dBitRenderTarget->CreateSolidColorBrush(color, &brush);

	_dBitRenderTarget->FillEllipse(el, brush);

	NEW_SAFE_RELEASE(brush);
}


