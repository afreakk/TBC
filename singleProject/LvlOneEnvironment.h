#pragma once
#include "LightHandler.h"
#include "ParticleEffect.h"
#include "WeatherSnow.h"
class LvlOneEnvironment
{
public:
	LvlOneEnvironment();
	~LvlOneEnvironment();
	void update();
private:
	LightHandler m_lightHandler;
	std::vector<std::unique_ptr<WeatherSnow> >m_snowRenderers;
	std::unique_ptr<SnowInstance> m_snowParticles;
	void initSnow();
};

