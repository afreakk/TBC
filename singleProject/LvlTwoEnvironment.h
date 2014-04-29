#pragma once
#include "LightHandler.h"
#include "ParticleEffect.h"
#include "WeatherSnow.h"
class LvlTwoEnvironment
{
public:
	LvlTwoEnvironment();
	~LvlTwoEnvironment();
	void update();
private:
	std::vector<std::unique_ptr<WeatherSnow> >m_snowRenderers;
	//std::unique_ptr<SnowInstance> m_snowParticles;
	void initSnow();
};
