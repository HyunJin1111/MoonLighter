#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init()
{
	return S_OK;
}

void iniDataManager::release()
{
}

void iniDataManager::addData(const char * subject, const char * title, const char * body)
{
	tagIniData iniData;
	iniData.subject = subject;
	iniData.title = title;
	iniData.body = body;

	arrIniData vIniData;
	vIniData.push_back(iniData);

	_vIniData.push_back(vIniData);
}

void iniDataManager::iniSave(const char * fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	//현재 디렉토리 경로를 받아와주는 함수
	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vIniData.size(); ++i)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].subject, vData[0].title, vData[0].body, str);

		vData.clear();
	}

	_vIniData.clear();

}

char* iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {};
	GetPrivateProfileString(subject, title, "", dataBuffer, 64, str);

	return dataBuffer;
}
char* iniDataManager::loadDataString2(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {};
	GetPrivateProfileString(subject, title, "", dataBuffer2, 64, str);

	return dataBuffer2;
}

int iniDataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);


	return GetPrivateProfileInt(subject, title, 0, str);
}

