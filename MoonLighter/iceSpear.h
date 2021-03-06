#pragma once
#include "gameNode.h"
#include <vector>


// 이거 파이어볼 시그니처


struct tagiceSpear
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

};

class iceSpear : public gameNode
{
private:
	vector<tagiceSpear>			_vSkill;
	vector<tagiceSpear>::iterator _viSkill;

	int _x2;
	float _range;
	int _SkillMax;
	float _angle;
	int _time;
	bool _go;
public:
	iceSpear() {};
	~iceSpear() {};

	HRESULT init(int skillMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);


	void move();
	void moveGo();

	void removeSkill(int arrNum);


	vector<tagiceSpear> getVSkill() { return _vSkill; }
	vector<tagiceSpear>::iterator getViSkill() { return _viSkill; }

};