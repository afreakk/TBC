#include "GUIBar.h"
#pragma once
static const Ogre::Real BAR_HEIGHT = 0.1f;
static const Ogre::Real BAR_WIDTH = BAR_HEIGHT*3.726744186046512f;
static const Ogre::Real BAR_SPACING = 0.01f;
class HealthBar : public GUIBar
{
public:
    HealthBar() 
    : GUIBar(BAR_SPACING, BAR_SPACING, BAR_WIDTH ,BAR_HEIGHT ,"health")
    { }
};
class EnergyBar : public GUIBar
{
public:
	EnergyBar()
	: GUIBar(BAR_SPACING, BAR_SPACING*2.0f+BAR_HEIGHT, BAR_WIDTH, BAR_HEIGHT, "energy")
	{	}
};