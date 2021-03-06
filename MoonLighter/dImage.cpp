#include "stdafx.h"
#include "dImage.h"

dImage::dImage()
	: _imageInfo(NULL),
	_fileName(NULL),
	_wicFactory(NULL),
	_bitDecoder(NULL),
	_bitFrame(NULL),
	_wicConverter(NULL)
{
}

dImage::~dImage()
{
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = fileName;

	HRESULT hr;

	//WICFactory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory생성 후 decoder생성(이미지 파일 정보 담은 컨테이너)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}
	
	//decoder에서 이미지 프레임 추출
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//컨버터 생성
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//컨버터에 추출한 이미지 프레임 넣어서 변환
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//실제 그리기 영역에 비트맵 형식으로 로드
	if (SUCCEEDED(hr)) {
		hr = D2DMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return S_OK;
}

HRESULT dImage::init(LPCWCHAR fileName, int width, int height, int frameX, int frameY)
{
	if (_imageInfo != NULL) release();

	_imageInfo = new IMAGE_INFO;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	_fileName = fileName;

	HRESULT hr = E_FAIL;

	//WICFactory 생성
	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_wicFactory));

	//WICFactory생성 후 decoder생성(이미지 파일 정보 담은 컨테이너)
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateDecoderFromFilename(_fileName, nullptr,
			GENERIC_READ, WICDecodeMetadataCacheOnDemand, &_bitDecoder);
	}

	//decoder에서 이미지 프레임 추출
	if (SUCCEEDED(hr)) {
		hr = _bitDecoder->GetFrame(0, &_bitFrame);
	}

	//컨버터 생성
	if (SUCCEEDED(hr)) {
		hr = _wicFactory->CreateFormatConverter(&_wicConverter);
	}

	//컨버터에 추출한 이미지 프레임 넣어서 변환
	if (SUCCEEDED(hr)) {
		_wicConverter->Initialize(_bitFrame,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			nullptr,
			0.0f,
			WICBitmapPaletteTypeCustom
		);
	}

	//실제 그리기 영역에 비트맵 형식으로 로드
	if (SUCCEEDED(hr)) {
		hr = D2DMANAGER->getRenderTarget()->CreateBitmapFromWicBitmap(_wicConverter, nullptr, &_imageInfo->bitMap);
	}

	return hr;
}

void dImage::release()
{
	if (_imageInfo)
	{
		//이미지 정보 해제
		SAFE_RELEASE2(_imageInfo->bitMap);
		SAFE_DELETE(_imageInfo);
	}

	//SAFE_DELETE(_fileName);
	//이미지 로드용 객체 해제
	SAFE_RELEASE2(_wicFactory);
	SAFE_RELEASE2(_bitDecoder);
	SAFE_RELEASE2(_bitFrame);
	SAFE_RELEASE2(_wicConverter);
}

void dImage::render(float opacity)
{
	D2D1_RECT_F destRect = dRectMake(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
	
	
	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::render(int destX, int destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->width, _imageInfo->height);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::render(int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sourWidth, sourHeight);
	D2D1_RECT_F sourRect = dRectMake(sourX, sourY, sourWidth, sourHeight);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
	

}

void dImage::frameRender(int destX, int destY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	D2D1_RECT_F sourRect = dRectMake(
		_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::frameRender(int destX, int destY, int currentFrameX, int currentFrameY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight);
	D2D1_RECT_F sourRect = dRectMake(
currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight,
		_imageInfo->frameWidth, _imageInfo->frameHeight);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);
}

void dImage::aniRender(int destX, int destY, animation * ani)
{


	render( destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());

}

void dImage::aniRender(int destX, int destY, float angle, animation * ani)
{
	D2D1_POINT_2F pt = { ani->getFrameWidth(),  ani->getFrameHeight() };
	render(destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
	D2DMANAGER->getBitRenderTarget()->SetTransform(Matrix3x2F::Rotation(angle, pt));
	//D2DMANAGER->getBitRenderTarget()->SetTransform(Matrix3x2F::Identity());

}

void dImage::scaleRender(int destX, int destY, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, _imageInfo->width * sizeX, _imageInfo->height* sizeY);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect, opacity);
}

void dImage::scaleRender(int destX, int destY, int sourX, int sourY, int sourwidth, int sourheight, float sizeX, float sizeY, float opacity)
{
	D2D1_RECT_F destRect = dRectMake(destX, destY, sourwidth* sizeX, sourheight* sizeY);
	D2D1_RECT_F sourRect = dRectMake(sourX, sourY, sourwidth* sizeX, sourheight* sizeY);

	//rendertarget을 불러와서 이미지의 비트맵을 그려준다
	D2DMANAGER->getBitRenderTarget()->DrawBitmap(_imageInfo->bitMap, destRect,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sourRect);

}


