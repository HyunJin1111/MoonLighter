#pragma once
#include "gameNode.h"
#include "aStar.h"
#include "enemyProgressBar.h"

enum MINIBOSS_STATE
{
	MINIBOSS_IDLE,
	MINIBOSS_WALK,
	MINIBOSS_SMASH,
	MINIBOSS_SWORD
};

enum MINIBOSS_DIRECTION
{
	MINIBOSS_DOWN,
	MINIBOSS_UP,
	MINIBOSS_LEFT,
	MINIBOSS_RIGHT
};
struct tagMiniBoss
{
	float x, y;
	int count;
	int currentFrameX, currentFrameY;
	float speed;
	int power;
	RECT rc;
	RECT hitRc;
	RECT attackRc;
	RECT attack2Rc;
	dImage* img;
	MINIBOSS_STATE state;
	MINIBOSS_DIRECTION direction;
	int rand;
	float angle;
	float alpha;
	bool changeState;
	float currentHp, maxHp;
	//적 피격
	bool enemyHit;
	bool enemyHitTime;
	int enemyHitCount;
};

class miniBoss : public gameNode
{
private:
	tagMiniBoss _miniBoss;
	aStar* _aStar;
	enemyProgressBar* _hpBar;

	int ran;

public:
	miniBoss();
	~miniBoss();


	HRESULT init(float x, float y, RECT player, int diffrentX, int diffrentY);
	void release();
	void update(float distance, int diffrentX, int diffrentY, RECT player);
	void render();
	void hpRender();

	void setMiniBoss();
	void miniBossState();
	void miniBossMove();




	//get, set 접근
	tagMiniBoss getMiniBoss() { return _miniBoss; }

	void setMiniBossX(float x) { _miniBoss.x = x; }
	void setMiniBossY(float y) { _miniBoss.y = y; }
	void setMiniBossAngle(float angle) { _miniBoss.angle = angle; }
	void setMiniBossRc(RECT rc) { _miniBoss.rc = rc; }
	void setMiniBossAttack1Rc(RECT rc) { _miniBoss.attackRc = rc; }
	void setMiniBossAttack2Rc(RECT rc) { _miniBoss.attack2Rc = rc; }
	void setMiniBossHitRc(RECT rc) { _miniBoss.hitRc = rc; }
	void setMiniBossImage(dImage* img) { _miniBoss.img = img; }
	void setMiniBossImage(MINIBOSS_STATE state) { _miniBoss.state = state; }
	void setMiniBossImage(MINIBOSS_DIRECTION direction) { _miniBoss.direction = direction; }

	void setMiniBossCurrentHp(float hp) { _miniBoss.currentHp = hp; }
	void setMiniBossEnemyHit(bool enemyHit) { _miniBoss.enemyHit = enemyHit; }
	void setMiniBossEnemyHitTime(bool enemyHitTime) { _miniBoss.enemyHitTime = enemyHitTime; }
	void setMiniBossEnemyHitCount(int enemyHitCount) { _miniBoss.enemyHitCount = enemyHitCount; }
};

