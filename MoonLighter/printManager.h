#pragma once
#include "singletonBase.h"

class printManager : public singletonBase<printManager>
{
private:
	printManager() {};
	~printManager() {};

	friend singletonBase;

	char _text[128];
	bool _debug;

public:
	

	HRESULT init();
	void release();

	void setDebug(bool debug) { _debug = debug; }
	bool isDebug() { return _debug; }
};
