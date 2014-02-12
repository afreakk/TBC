#include "GUIBar.h"
#pragma once
static const Ogre::Real BAR_WIDTH = 0.3;
static const Ogre::Real BAR_HEIGHT = 0.05;
static const Ogre::Real BAR_SPACING = 0.025;
class HealthBar : public GUIBar
{
public:
    HealthBar() 
    : GUIBar(BAR_SPACING, 1.0-(BAR_SPACING+BAR_HEIGHT), BAR_WIDTH ,BAR_HEIGHT ,"HealthBar")
    { }
};
class EnergyBar : public GUIBar
{
public:
	EnergyBar()
	:GUIBar(1.0-(BAR_SPACING+BAR_WIDTH), 1.0-(BAR_SPACING+BAR_HEIGHT), BAR_WIDTH, BAR_HEIGHT, "EnergyBar")
	{	}
};
