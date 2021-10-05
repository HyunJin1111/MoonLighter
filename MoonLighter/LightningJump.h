#pragma once
#include "gameNode.h"
#include <vector>



struct tagLightningJump
{
	dImage* skillImage;		// �̹��� 
	Vector2 _RL, _RR, _RT, _RB; //����Ʈ<- �浹�Ҷ� �������
	RECT rc;				// ��Ʈ
	float x, y;				// ��ǥ(�ǽð�)
	float angle;			// ����
	float radius;			// ������
	float speed;			// ���ǵ�
	float fireX, fireY;		// �߻�� ó�� ��ǥ(�߻�� ��ǥ)
	bool isFire;			//�ߵ�
	int count;				// ������ī��Ʈ��
	int _time;

};

class LightningJump : public gameNode
{
private:
	vector<tagLightningJump>			_vSkill;
	vector<tagLightningJump>::iterator _viSkill;

	int _x2;
	float _range;
	int _SkillMax;
	float _angle;
	int _time;
	burn* _burn;
public:
	LightningJump() {};
	~LightningJump() {};

	HRESULT init(int skillMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);


	void move();


	void removeSkill(int arrNum);


	vector<tagLightningJump> getVSkill() { return _vSkill; }
	vector<tagLightningJump>::iterator getViSkill() { return _viSkill; }

};