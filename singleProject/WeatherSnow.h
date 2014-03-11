#pragma once
#include "ParticleEffect.h"
class WeatherSnow : public ParticleEffect
{
public:
	WeatherSnow();
	~WeatherSnow();
	void update();
private:
	Ogre::Real m_height;
};

