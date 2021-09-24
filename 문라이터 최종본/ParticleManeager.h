#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class Particle;

class ParticleManeager : public singletonBase<ParticleManeager>
{
private:
	//생산
	typedef vector<Particle*>								arrParticles;
	typedef vector<Particle*>::iterator						iterParticles;
	//가공
	typedef map<string, arrParticles>						arrParticle;
	typedef map<string, arrParticles>::iterator				iterParticle;
	//포장
	typedef vector<map<string, arrParticles>>				arrTotalParticle;
	typedef vector<map<string, arrParticles>>::iterator		iterTotalParticles;

private:
	arrTotalParticle _vTotalParticle;

public:
	ParticleManeager();
	~ParticleManeager();

	HRESULT init();
	void release();
	void update();
	void render();

	void addParticle(string ParticleName, const char* imageName, int imageWidth,
		int imageHeight, int ParticletWidth, int ParticleHeight, int fps, float elapsed, int buffer);

	void play(string effectName, int x, int y, float angle);
};