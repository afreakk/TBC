#pragma once
#include "LightHandler.h"
class LvlOneEnvironment
{
public:
	LvlOneEnvironment();
	~LvlOneEnvironment();
	void update();
private:
	LightHandler m_lightHandler;
};

