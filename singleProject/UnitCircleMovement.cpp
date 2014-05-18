#include "stdafx.h"
#include "UnitCircleMovement.h"
#include "LaneSettings.h"
#include <math.h>
Ogre::Vector3 UnitCircleMovement::VectorFromPolar(PolarCoordinates p)
{
	return Ogre::Vector3(Ogre::Math::Sin(p.theta)*p.radius,p.h,Ogre::Math::Cos(p.theta)*p.radius);
}
PolarCoordinates UnitCircleMovement::PolarFromVector(Ogre::Vector3 p)
{
	PolarCoordinates polar;
	polar.h = p.y;
	polar.theta = thetaFromVector(p);
	polar.radius = radiusFromVector(p);
	return polar;
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
		p.theta += Ogre::Math::PI/12.0f;
		break;
	case NormalDirection::dirLeft:
		p.theta -= Ogre::Math::PI/12.0f;
		break;
	default:
		return;
		break;
	}
	node->lookAt(VectorFromPolar(p),Ogre::Node::TransformSpace::TS_WORLD);
}

void keepWithinMax(Real* d)
{
	while (*d > Math::PI*2.0f)
		*d -= Math::PI*2.0f;
	while (*d < 0.0)
		*d += Math::PI*2.0f;
}
unsigned energyCostOf(PolarCoordinates a, PolarCoordinates b)
{
	keepWithinMax(&a.theta);
	keepWithinMax(&b.theta);
	return static_cast<unsigned>(round( Ogre::Math::Abs(a.theta - b.theta)*200.0 ));
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
	norm.theta = thetaFromVector(vec);
	norm.radius = radiusFromVector(vec);
}
Ogre::Real thetaFromVector(const Ogre::Vector3& pos)
{
	return atan2(pos.x, pos.z);
}
Ogre::Real radiusFromVector(const Ogre::Vector3& pos)
{
	return sqrt(pos.z*pos.z + pos.x*pos.x);
}
Vector3 vectorFromTumbleDirection(Vector3 playerPos, TUMBLE_DIRECTION direction)
{
	PolarCoordinates polar;
	vectorToPolar(playerPos, polar);
	switch (direction)
	{
	case TUMBLE_DIRECTION::DIRECTION_IN:
		polar.radius -= LaneSettings::getSingleton().getIncrement();
		break;
	case TUMBLE_DIRECTION::DIRECTION_OUT:
		polar.radius += LaneSettings::getSingleton().getIncrement();
		break;
	default:
		assert(0);
		break;
	}
	Real shortestDistance = 100000.0;
	int laneIndex = -1;
	for (unsigned i = 0; i < LaneSettings::getSingleton().getLaneCount(); i++)
	{
		auto distance = abs(polar.radius - LaneSettings::getSingleton().getLane(i));
		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			laneIndex = static_cast<int>(i);
		}
	}
	assert(laneIndex > -1);
	polar.radius = LaneSettings::getSingleton().getLane(laneIndex);
	return UnitCircleMovement::VectorFromPolar(polar);
}
PolarCoordinates polarFromStarting(Real r, unsigned laneIdx)
{
	return PolarCoordinates(r, LaneSettings::getSingleton().getLane(laneIdx), LaneSettings::getSingleton().getHeight());
}
