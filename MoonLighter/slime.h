#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "enemyProgressBar.h"

enum SLIMESTATE 
{
	SLIME_IDLE,
	SLIME_WALK,
	SLIME_ATTACK,
	SLIME_DIE,
	SLIME_RANDOM
};
struct tagSlime
{
	float x, y;
	float angle;
	float alpha;
	int currentFrameX, currentFrameY;
	int count;
	int speed;
	int power;
	float maxHp, currentHp;
	//Àû ÇÇ°Ý
	bool enemyHit;
	bool enemyHitTime;
	int enemyHitCount;
	bool die;
	int rand;
	int walkRand;								//·£´ý ÀÌµ¿°ª
	int walkCount;								//·£´ý Ä«¿îÆ® °ª
	float angleRand1, angleRand2;				//·£´ý ¾Þ±Û°ª1
	int backGroundNum;							//·£´ý ¾Þ±Û°ª2
	dImage* img;
	RECT rc;
	RECT hitRc;
	RECT moveRect;
	RECT attackRect;
	RECT powerRect;
	RECT upLeft, upRight, downLeft, downRight, leftUp, leftDown, rightUp, rightDown;
	SLIMESTATE state;
	aStar* _aStar;
	enemyProgressBar* hpBar;
	bool changeState;
};


class slime : public gameNode
{
private:
	

	vector<tagSlime> _vSlime;
	


public:
	slime();
	~slime();

	HRESULT init(int x, int y, RECT player, int diffrentX, int diffrentY, int backGroundNum);
	void release();
	void update( int diffrentX, int diffrentY, RECT player, int backNum);
	void render();

	void erase(int num);
	void slimeState();
	void slimeMove();

	vector<tagSlime> getSlime() { return _vSlime; }
	void setSlimeX(int index, float x) { _vSlime[index].x = x; }
	void setSlimeY(int index, float y) { _vSlime[index].y = y; }
	void setSlimeCurrentHp(int index, int currentHp) { _vSlime[index].currentHp = currentHp; }
	void setEnemyHit(int index, bool hit) { _vSlime[index].enemyHit = hit; }
	void setEnemyHitTime(int index, bool enemyHitTime) { _vSlime[index].enemyHitTime = enemyHitTime; }
	void setEnemyHitCount(int index, int enemyCount) { _vSlime[index].enemyHitCount = enemyCount; }
	void setEnemyState(int index, SLIMESTATE state) { _vSlime[index].state = state; }

	aStar* getAstar(int index) { return _vSlime[index]._aStar; }
};

