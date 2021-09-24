#include "stdafx.h"
#include "bullets.h"

HRESULT bullet::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
}

void bullet::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();	_viBullet++)
	{
		// 렌더
		if (_viBullet->direction == 0)
		{
			_viBullet->bulletImage->Frame_scale_start(_viBullet->x, _viBullet->y, -1, 1);

			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 0);

			_viBullet->bulletImage->scale_end();
		}
		else
		{
			_viBullet->bulletImage->FrameRender(
				_viBullet->rc.left,
				_viBullet->rc.top,
				_viBullet->bulletImage->getFrameX(), 0);
		}

		_viBullet->count++;

		// 프레임 속도 조절용 카운트
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			_viBullet->count = 0;
		}

		//최대 프레임보다 커지면
		if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
		{
			_viBullet->bulletImage->setFrameX(0);
		}
	}
}

void bullet::fire(LPCWSTR imagename, float x, float y, float width, float height,
	float frameX, float frameY, float angle, int direction)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(imagename, width, height, frameX, frameY);
	bullet.speed = 4.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.direction = direction;

	bullet.rc = D2DMANAGER->RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	_vBullet.push_back(bullet);

}

void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void bullet::removeBullet(int arrNum)
{
	//벡터의 값을 지울떈  erase()
	_vBullet.erase(_vBullet.begin() + arrNum);
}

/**************************************** 갑옷이나 양이 조각날때 사용하는 불렛 *******************************************************/

HRESULT fragment::init(int bulletMax, float range)
{
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void fragment::release()
{
}

void fragment::update()
{
	move();
}

void fragment::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		// 렌더
		_viBullet->bulletImage->render(
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->opacity);

		_viBullet->opacity -= 0.007f;

		if (_viBullet->opacity <= 0.0f)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
			_viBullet++;
	}
}

void fragment::fire(LPCWSTR filename, float x, float y, float width, float height, int _direction)
{
	//최대갯수보다 더 생성되려고 하면 하지않는다
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->D_Init(filename, width, height);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.speed = 3.0f;
	bullet.opacity = 1.0f;
	bullet.rc = D2DMANAGER->RectMake(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());
	bullet.width = bullet.rc.right - bullet.rc.left;
	bullet.height = bullet.rc.bottom - bullet.rc.top;
	bullet.direction = _direction;

	bullet.jump_power = RND->getFromFloatTo(0.0f, 6.0f);
	bullet.gravity = 0.2f;

	_vBullet.push_back(bullet);
}

void fragment::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); _viBullet++)
	{
		_viBullet->x += _viBullet->speed * _viBullet->direction;
		_viBullet->y -= _viBullet->jump_power - _viBullet->gravity;

		_viBullet->gravity += 0.2f;

		_viBullet->rc = D2DMANAGER->RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());
	}
}

void fragment::removeMissile(int arrNum)
{
	_vBullet[arrNum].bulletImage->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}

void fragment::set_rect(int num, float val)
{
	_vBullet[num].rc.bottom = val;
	_vBullet[num].rc.top = _vBullet[num].rc.bottom - _vBullet[num].height;
}

void fragment::set_gravity(int num)
{
	_vBullet[num].gravity = 0.0f;
	_vBullet[num].speed = 0.0f;
	_vBullet[num].jump_power = 0.0f;
}

void fragment::set_direction(int num)
{
	_vBullet[num].direction = _vBullet[num].direction * -1;
}
