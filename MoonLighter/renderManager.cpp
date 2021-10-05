#include "stdafx.h"
#include "renderManager.h"
#include <algorithm>

renderManager::renderManager()
{
}

renderManager::~renderManager()
{
}

HRESULT renderManager::init()
{
	return S_OK;
}

void renderManager::release()
{
}

void renderManager::update()
{
}

void renderManager::render()
{
	for (int i = 0; _vImage.size(); ++i) 
	{
		_vImage[i].img->frameRender(0, 0);
	}
}

void renderManager::pushBackImage(float bottom)
{
	tagImageRender renderImg;
	ZeroMemory(&renderImg, sizeof(tagImageRender));
	renderImg.rc.bottom = bottom;

	_vImage.push_back(renderImg);
}

void renderManager::clearImage()
{
	_vImage.clear();
}



bool renderManager::compare(tagImageRender * a, tagImageRender * b)
{
	return a->rc.bottom < b->rc.bottom;
}
void renderManager::sort_hyun()
{
	
}
