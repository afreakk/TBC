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
	WeatherSnow m_snow;
};

