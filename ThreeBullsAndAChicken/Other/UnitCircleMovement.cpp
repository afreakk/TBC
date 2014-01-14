#include "stdafx.h"
#include "UnitCircleMovement.h"

Ogre::Vector3 UnitCircleMovement::posFromR(const Ogre::Real& r,const Ogre::Real& distance,const Ogre::Real& height)
{
	return Ogre::Vector3(Ogre::Math::Sin(r)*distance,height,Ogre::Math::Cos(r)*distance);
}