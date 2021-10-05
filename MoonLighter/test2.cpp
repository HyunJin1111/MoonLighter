#include "stdafx.h"
#include "test2.h"

HRESULT test2::init()
{
	CAMERAMANAGER->setBackScreenSize(3840, 2160);
	return S_OK;
}

void test2::release()
{
}

void test2::update()
{
}

void test2::render()
{
}
