#pragma once
#include "stdafx.h"
enum class NormalDirection
{
	Left,
	Right,
	None
};
struct PolarCoordinates
{
	Ogre::Real r;
	Ogre::Real d;
	Ogre::Real h;
	PolarCoordinates() :r(0), d(0), h(0)
	{
	}
	PolarCoordinates(Real radian, Real distance, Real height) :r(radian), d(distance), h(height)
	{
	}

};
class UnitCircleMovement
{
public:
	static Ogre::Vector3 posFromR(PolarCoordinates p);
	static void normalSetPosition(Ogre::SceneNode* node, PolarCoordinates);
	static void normalSetDirection(Ogre::SceneNode* node, PolarCoordinates, NormalDirection);
};


void keepWithinMax(Real*);
bool isWithinRange(Real, Real, Real);
unsigned energyCostOf(PolarCoordinates, PolarCoordinates);
void vectorToNormal(const Vector3 vec, PolarCoordinates&);