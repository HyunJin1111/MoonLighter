
#include "stdafx.h"
#include "utils.h"

namespace UJN_UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}


	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);
		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}


	bool IsCollision(const RECT& rc1, const ENEMYRECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;
		return false;
	}

	bool IsCollision(const RECT& rc1, const RECT& rc2)
	{
		if ((rc1.left <= rc2.right && rc1.right >= rc2.left) &&
			(rc1.top <= rc2.bottom && rc1.bottom >= rc2.top)) return true;
		return false;
	}

	bool IntersectRectReaction2(RECT*const rcMove, const RECT*const rcHold)
	{
		RECT rcInter = RectMakeCenter(100, 100, 100, 100);;


		float interW = (float)rcInter.right - (float)rcInter.left;
		float interH = (float)rcInter.bottom - (float)rcInter.top;

		if (Math::FloatEqual(interW, interH))
		{
			if (Math::FloatEqual(rcInter.left, rcHold->left))
			{
				rcMove->left -= interW;
				rcMove->right -= interW;

			}
			else if (Math::FloatEqual(rcInter.right, rcHold->right))
			{
				rcMove->left += interW;
				rcMove->right += interW;

			}
			//위
			if (Math::FloatEqual(rcInter.top, rcHold->top))
			{
				rcMove->top -= interH;
				rcMove->bottom -= interH;

			}
			//아래
			else if (Math::FloatEqual(rcInter.bottom, rcHold->bottom))
			{
				rcMove->top += interH;
				rcMove->bottom += interH;

			}
		}
		else if (interW < interH)
		{
			if (Math::FloatEqual(rcInter.left, rcHold->left))
			{
				rcMove->left -= interW;
				rcMove->right -= interW;

			}
			else if (Math::FloatEqual(rcInter.right, rcHold->right))
			{
				rcMove->left += interW;
				rcMove->right += interW;

			}

		}
		else
		{
			//위
			if (Math::FloatEqual(rcInter.top, rcHold->top))
			{
				rcMove->top -= interH;
				rcMove->bottom -= interH;

			}
			//아래
			else if (Math::FloatEqual(rcInter.bottom, rcHold->bottom))
			{
				rcMove->top += interH;
				rcMove->bottom += interH;

			}
		}

		return true;
	}

	char * ConvertWCtoC(wchar_t * str)
	{
		//반환할 char* 변수 선언
		char* pStr;

		//입력받은 wchar_t 변수의 길이를 구함
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//char* 메모리 할당
		pStr = new char[strSize];

		//형 변환 
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}

	const char * ConvertWCtoC(const wchar_t * str)
	{
		//반환할 char* 변수 선언
		char* pStr;

		//입력받은 wchar_t 변수의 길이를 구함
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		//char* 메모리 할당
		pStr = new char[strSize];

		//형 변환 
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}

	wchar_t *ConvertCtoWC(char * str)
	{
		//wchar_t형 변수 선언
		wchar_t* pStr;
		//멀티 바이트 크기 계산 길이 반환
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//wchar_t 메모리 할당
		pStr = new WCHAR[strSize];
		//형 변환
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
		return pStr;
	}

	const wchar_t *ConvertCtoWC(const char * str)
	{
		//wchar_t형 변수 선언
		wchar_t* pStr;
		//멀티 바이트 크기 계산 길이 반환
		int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
		//wchar_t 메모리 할당
		pStr = new WCHAR[strSize];
		//형 변환
		MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
		return pStr;
	}

	wstring ConvertStoWS(string str)
	{
		wstring w_str = L"";

		w_str.assign(str.begin(), str.end());

		return w_str;
	}

	string ConvertWStoS(wstring w_str)
	{
		string str;

		str.assign(w_str.begin(), w_str.end());

		return str;
	}
}

	