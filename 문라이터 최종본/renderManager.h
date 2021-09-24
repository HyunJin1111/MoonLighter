#pragma once
#include "singletonBase.h"
#include <vector>

struct tagImageRender
{
	dImage* img;
	RECT rc;
	float x, y;
};

class renderManager : public singletonBase<renderManager>
{
private:
	vector<tagImageRender> _vImage;
public:
	renderManager();
	~renderManager();

	HRESULT init();
	void release();
	void update();
	void render();
	void pushBackImage(float bottom);
	void clearImage();
	bool compare(tagImageRender * a, tagImageRender * b);
	void sort_hyun();

	vector<tagImageRender> getVImage() { return _vImage; }
};

