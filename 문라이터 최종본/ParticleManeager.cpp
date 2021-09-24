#include "stdafx.h"
#include "ParticleManeager.h"
#include "Particle.h"


ParticleManeager::ParticleManeager()
{
}

ParticleManeager::~ParticleManeager()
{
}

HRESULT ParticleManeager::init()
{
	return S_OK;
}

void ParticleManeager::release()
{
	iterTotalParticles vIter;
	iterParticle mIter;

	vIter = _vTotalParticle.begin();

	for (; vIter != _vTotalParticle.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != NULL)
			{
				iterParticles vArrIter = mIter->second.begin();
				for (vArrIter; vArrIter != mIter->second.end();)
				{
					if (*vArrIter)
					{
						(*vArrIter)->release();
						delete *vArrIter;
						vArrIter = mIter->second.erase(vArrIter);
					}
					else
						++vArrIter;
				}
				mIter->second.clear();
			}
			else ++mIter;
		}
	}

}

void ParticleManeager::update()
{
	iterTotalParticles vIter;
	iterParticle mIter;

	for (vIter = _vTotalParticle.begin(); vIter != _vTotalParticle.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterParticles vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void ParticleManeager::render()
{
	iterTotalParticles vIter;
	iterParticle mIter;

	for (vIter = _vTotalParticle.begin(); vIter != _vTotalParticle.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			iterParticles vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}

}

void ParticleManeager::addParticle(string effectName, const char* imageName, int imageWidth, int imageHeight, int effectWidth, int effectHeight, int fps, float elapsed, int buffer)
{
	dImage*		img;
	arrParticles	vParticletBuffer;
	arrParticle 	mArrParticle;

	char temp[128]; // 1바이트
	strcpy_s(temp, sizeof(temp), imageName);

	wchar_t img_name[128]; // 2 바이트
	MultiByteToWideChar(0, 0, temp, sizeof(temp), img_name, sizeof(img_name) / 2);
	LPCWSTR image_name = img_name;

	if (IMAGEMANAGER->findDImage(imageName))
	{
		img = IMAGEMANAGER->findDImage(imageName);
	}
	else
	{
		img = IMAGEMANAGER->addFrameDImage(imageName, image_name, imageWidth, imageHeight, imageWidth / effectWidth, imageHeight / effectHeight);
	}


	for (int i = 0; i < buffer; ++i)
	{
		vParticletBuffer.push_back(new Particle);
		vParticletBuffer[i]->init(img, effectWidth, effectHeight, fps, elapsed);
	}

	mArrParticle.insert(pair<string, arrParticles>(effectName, vParticletBuffer));

	_vTotalParticle.push_back(mArrParticle);

}

void ParticleManeager::play(string effectName, int x, int y, float angle)
{
	iterTotalParticles vIter;
	iterParticle		mIter;

	for (vIter = _vTotalParticle.begin(); vIter != _vTotalParticle.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (!(mIter->first == effectName)) break;

			iterParticles vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y, angle);
				return;
			}
		}
	}
}
