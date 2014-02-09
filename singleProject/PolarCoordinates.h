#pragma once
#include "OgrePrerequisites.h"
class PolarCoordinates
{
public:
	PolarCoordinates(Ogre::Real radian, Ogre::Real distance, Ogre::Real height);
	PolarCoordinates();
	~PolarCoordinates();
	Ogre::Real r;
	Ogre::Real d;
	Ogre::Real h;
};

