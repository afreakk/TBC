#pragma once
#include "stdafx.h"
const unsigned NORMAL_LANES_COUNT = 3;
const Real NORMAL_INCREMENT = 1.0;
const Real NORMAL_FIRST_LANE = 5.0;
const Real NORMAL_LANES[NORMAL_LANES_COUNT] = {NORMAL_FIRST_LANE, NORMAL_FIRST_LANE+(NORMAL_INCREMENT*1), NORMAL_FIRST_LANE+(NORMAL_INCREMENT*2) };
const Real NORMAL_LANE_HEIGHT = 0.0;

enum class NormalDirection
{
	Left,
	Right,
	None
};
enum class TUMBLE_DIRECTION
{
	DIRECTION_IN,
	DIRECTION_OUT,
	DIRECTION_NONE
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
	static Ogre::Vector3 VectorFromPolar(PolarCoordinates p);
	static void polarSetPosition(Ogre::SceneNode* node, PolarCoordinates);
	static void polarSetDirection(Ogre::SceneNode* node, PolarCoordinates, NormalDirection);
};


void keepWithinMax(Real*);
bool isWithinRange(Real, Real, Real);
unsigned energyCostOf(PolarCoordinates, PolarCoordinates);
void vectorToPolar(const Vector3 vec, PolarCoordinates&);
Vector3 vectorFromTumbleDirection(Vector3 playerPos, TUMBLE_DIRECTION direction);
