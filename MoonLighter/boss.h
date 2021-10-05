#pragma once
#include "gameNode.h"
#include "enemyProgressBar.h"
#include "bossState.h"
#include "bossIdle.h"
#include "bossDie.h"
#include "bossAttack1.h"
#include "bossAttack1Reverse.h"
#include "bossAttack2.h"

enum BOSSSTATE
{
	BOSS_IDLE,
	BOSS_ATTACK1_GO,
	BOSS_ATTACK1_REVERSE,
	BOSS_ATTACK2,
	BOSS_DIE
};

struct tagBoss
{
	float x, y;
	int currentFrameX, currentFrameY;
	int count;
	int power;
	dImage* img;
	dImage* hpImg;
	RECT rc;
	RECT hitRc;
	RECT attackRc2;
	float alpha;
	float currentHp, maxHp;
	BOSSSTATE state;
	bool isAttack1;
	//적 피격
	bool enemyHit;
	bool enemyHitTime;
	int enemyHitCount;
};
class boss : public gameNode
{
private:
	enemyProgressBar* _hpBar;
	bossState* _bossState;
	//보스
	tagBoss _boss;
	tagBoss _bossArm;

	dImage* _hpLeft;
	dImage* _hpRight;


	float _attack1Y;
	bool _isAttack1XY;
public:
	boss();
	~boss();


	HRESULT init(float x, float y);
	void release();
	void update(float playerX, float playerY);
	void render();
	void InputHandle();

	//get set
	tagBoss getBoss() { return _boss; }

	void setBossCurrentHp(float hp) { _boss.currentHp = hp; }
	void setBossState(BOSSSTATE state) { _boss.state = state; }
	void setBossEnemyHit(bool hit) { _boss.enemyHit = hit; }
	void setBossEnemyHitCount(int hitCount) { _boss.enemyHitCount = hitCount; }
	void setBossEnemyHitTime(bool hit) { _boss.enemyHitTime = hit; }
	void setBossRect(RECT rc) { _boss.rc = rc; }
	void setBossAttack2Rect(RECT rc) { _boss.attackRc2 = rc; }
	void setBossImg(dImage* img) { _boss.img = img; }
	void setBossCurrentFrameX(int x) { _boss.currentFrameX = x; }
	void setBossCurrentFrameY(int y) { _boss.currentFrameY = y; }
	void setBossAttack1(bool attack) { _boss.isAttack1 = attack; }
	void setAttackY(float attack) { _attack1Y = attack; }

	tagBoss getBossArm() { return _bossArm; }

	void setBossArmCurrentFrameX(int x) { _bossArm.currentFrameX = x; }
	void setBossArmRect(RECT rc) { _bossArm.rc = rc; }
	void setBossArmX(float x) { _bossArm.x = x; }
	void setBossArmY(float y) { _bossArm.y = y; }


	float getAttackY() { return _attack1Y; }




};

