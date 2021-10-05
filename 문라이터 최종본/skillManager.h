#pragma once
#include "singletonBase.h"/*
#include "fireDash.h"
#include "fireCross.h"
#include "skill.h"
#include "iceSpear.h"
#include "waterZone.h"
#include "bubble.h"
#include "LightningWave.h"
#include "LightningJump.h"
#include "LightBeam.h"
#include "iceWall.h"
#include "frostWall.h"*/



class skillManager : public singletonBase<skillManager>
{
private:
	skillManager() {};
	~skillManager() {};

	friend singletonBase;

	//fireDash* _fireDash; //2��
	//fireCross* _fireCross; //1��
	//skill* _skill; // 0��
	//iceSpear* _iceSpear; //3��
	//waterZone* _waterZone; // 4��
	//bubble* _bubble; //5��
	//LightningWave* _LightningWave; //6��
	//LightningJump* _LightningJump;
	//LightBeam* _LightBeam;
	//iceWall* _iceWall;
	//frostWall* _frostWall;
	//int _skillType;
public:

	

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(int SkillNum,float x, float y, float angle);
	void keyUP();

};