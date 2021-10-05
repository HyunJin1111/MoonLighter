#pragma once
#define PI 3.14159f
#define PI2 PI * 2

#define RECT_WIDTH(rc) static_cast<float>(rc.right - rc.left)
#define RECT_HEIGHT(rc) static_cast<float>(rc.bottom - rc.top)
#define RECT_CENTER_X(rc) static_cast<float>((rc.left + rc.right) * 0.5f)
#define RECT_CENTER_Y(rc) static_cast<float>((rc.top + rc.bottom) * 0.5f)

//이미지 회전 시킬때 앵글 별 프레임 계산하기 위한 디파인
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)


namespace UJN_UTIL
{
	//거리가져오는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	float getAngle(float x1, float y1, float x2, float y2);


	//사각형 구조체
	typedef struct tagENEMYRECT
	{
		float left;
		float top;
		float right;
		float bottom;

		tagENEMYRECT() : left(0.0f), top(0.0f), right(0.0f), bottom(0.0f) {}
		tagENEMYRECT(float _left, float _top, float _right, float _bottom) :
			left(_left), top(_top), right(_right), bottom(_bottom) {}

		void Move(float dx, float dy)
		{
			left += dx;
			right += dx;
			top += dy;
			bottom += dy;
		}

		void Set(float _left, float _top, float _right, float _bottom)
		{
			left = _left;
			top = _top;
			right = _right;
			bottom = _bottom;
		}

		//레프트 탑으로 셋팅
		void SetLeftTopPos(float _left, float _top)
		{
			float width = getWidth();
			float height = getHeight();

			left = _left;
			top = _top;
			right = _left + width;
			bottom = _top + height;
		}

		void SetCenterPos(float centerX, float centerY)
		{
			float halfW = getWidth() * 0.5f;
			float halfH = getHeight() * 0.5f;

			left = centerX - halfW;
			top = centerY - halfH;
			right = centerX + halfW;
			bottom = centerY + halfH;
		}

		float getWidth(void) { return right - left; }
		float getHeight(void) { return bottom - top; }
	}ENEMYRECT, *LPENEMYRECT;

	//사각형이 사각형과 충돌했니?
	bool IsCollision(const RECT& rc1, const ENEMYRECT& rc2);
	bool IsCollision(const RECT& rc1, const RECT& rc2);
	bool IntersectRectReaction2(RECT*const rcMove, const RECT*const rcHold);
	//wchar_t 에서 char 로의 형변환 함수
	char * ConvertWCtoC(wchar_t * str);
	const char * ConvertWCtoC(const wchar_t * str);
	//char 에서 wchar_t 로의 형변환 함수
	wchar_t *ConvertCtoWC(char * str);
	const wchar_t *ConvertCtoWC(const char * str);
	//stirng 에서 wstring 으로 형 변환 함수
	wstring ConvertStoWS(string str);
	string ConvertWStoS(wstring w_str);
}