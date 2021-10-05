#pragma once
#include "gameNode.h"
#include <vector>
#include "burn.h"

// �̰� ���̾ �ñ״�ó


struct tagskill
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

};

class skill : public gameNode
{
private:
	vector<tagskill>			_vSkill;
	vector<tagskill>::iterator _viSkill;

	int _x2;
	float _range;
	int _SkillMax;
	float _angle;
	int _time;
	burn* _burn;
public:
	skill() {};
	~skill() {};

	HRESULT init(int skillMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);


	void move();


	void removeSkill(int arrNum);


	vector<tagskill> getVSkill() { return _vSkill; }
	vector<tagskill>::iterator getViSkill() { return _viSkill; }

};