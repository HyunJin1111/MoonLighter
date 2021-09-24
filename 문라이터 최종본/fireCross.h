#pragma once
#include "gameNode.h"
#include <vector>
#include "burn.h"


struct tagfireCross
{
	dImage* skillImage;		// 이미지 
	Vector2 _RL, _RR, _RT, _RB; //포인트<- 충돌할때 사용해줘
	RECT rc;				// 렉트
	float x, y;				// 좌표(실시간)
	float angle;			// 각도
	float radius;			// 반지름
	float speed;			// 스피드
	float fireX, fireY;		// 발사시 처음 좌표(발사된 좌표)
	bool isFire;			//발동
	int count;				// 프레임카운트용
	int _time;

};

class fireCross : public gameNode
{
private:
	vector<tagfireCross>			_vSkill;
	vector<tagfireCross>::iterator _viSkill;

	int _x2;
	float _range;
	int _SkillMax;
	float _angle;
	int _time;
	burn* _burn;
public:
	fireCross() {};
	~fireCross() {};

	HRESULT init(int skillMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);


	void move();


	void removeSkill(int arrNum);


	vector<tagfireCross> getVSkill() { return _vSkill; }
	vector<tagfireCross>::iterator getViSkill() { return _viSkill; }

};