#include "stdafx.h"
#include "UnitCircleMovement.h"
#include "LaneSettings.h"
using namespace Ogre;
Ogre::Vector3 UnitCircleMovement::VectorFromPolar(PolarCoordinates p)
{
	return Ogre::Vector3(Ogre::Math::Sin(p.r)*p.d,p.h,Ogre::Math::Cos(p.r)*p.d);
}
void UnitCircleMovement::polarSetPosition(Ogre::SceneNode* node, PolarCoordinates p)
{
	node->setPosition(VectorFromPolar(p));
}
void UnitCircleMovement::polarSetDirection(Ogre::SceneNode* node, PolarCoordinates p, NormalDirection direction)
{
	switch (direction)
	{
	case NormalDirection::dirRight:
		p.r += Ogre::Math::PI/12.0;
		break;
	case NormalDirection::dirLeft:
		p.r -= Ogre::Math::PI/12.0;
		break;
	default:
		return;
		break;
	}
	node->lookAt(VectorFromPolar(p),Ogre::Node::TransformSpace::TS_WORLD);
}

void keepWithinMax(Real* d)
{
	while (*d > Math::PI*2.0)
		*d -= Math::PI*2.0;
	while (*d < 0.0)
		*d += Math::PI*2.0;
}
#include <math.h>
unsigned energyCostOf(PolarCoordinates a, PolarCoordinates b)
{
	keepWithinMax(&a.r);
	keepWithinMax(&b.r);
	return static_cast<unsigned>(round( Ogre::Math::Abs(a.r - b.r)*100.0 ));
}
bool isWithinRange(Real r1, Real r2, Real distance)
{
	keepWithinMax(&r1);
	keepWithinMax(&r2);
	if (r1 >= r2 - distance && r1 <= r2 + distance)
		return true;
	return false;
}
void vectorToPolar(const Vector3 vec, PolarCoordinates& norm)
{
	norm.h = vec.y;
	norm.r = atan2(vec.x , vec.z);
	norm.d = sqrt(vec.z*vec.z + vec.x*vec.x);
}
Vector3 vectorFromTumbleDirection(Vector3 playerPos, TUMBLE_DIRECTION direction)
{
	PolarCoordinates polar;
	vectorToPolar(playerPos, polar);
	switch (direction)
	{
	case TUMBLE_DIRECTION::DIRECTION_IN:
		polar.d -= LaneSettings::getSingleton().getIncrement();
		break;
	case TUMBLE_DIRECTION::DIRECTION_OUT:
		polar.d += LaneSettings::getSingleton().getIncrement();
		break;
	default:
		assert(0);
		break;
	}
	Real shortestDistance = 100000.0;
	int laneIndex = -1;
	for (int i = 0; i < LaneSettings::getSingleton().getLaneCount(); i++)
	{
		auto distance = abs(polar.d - LaneSettings::getSingleton().getLane(i));
		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			laneIndex = i;
		}
	}
	assert(laneIndex > -1);
	polar.d = LaneSettings::getSingleton().getLane(laneIndex);
	return UnitCircleMovement::VectorFromPolar(polar);
}
PolarCoordinates polarFromStarting(Real r, unsigned laneIdx)
{
	return PolarCoordinates(r, LaneSettings::getSingleton().getLane(laneIdx), LaneSettings::getSingleton().getHeight());
}