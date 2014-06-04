#pragma once
#include "ConfigScriptLoader.h"
#include "ENUMNormalDirection.h"
#include "ENUMTumbleDirection.h"
#include "PolarCoordinates.h"
//todo this should be in UniversalGameObjects
class UnitCircleMovement
{
public:
	static Ogre::Vector3 VectorFromPolar(PolarCoordinates p);
	static PolarCoordinates PolarFromVector(Ogre::Vector3 p);
	static void polarSetPosition(Ogre::SceneNode* node, PolarCoordinates);
	static void polarSetDirection(Ogre::SceneNode* node, PolarCoordinates, NormalDirection);
};
void keepWithinMax(Ogre::Real*);
bool isWithinRange(Ogre::Real, Ogre::Real, Ogre::Real);
unsigned energyCostOf(const Ogre::Vector3& a, const Ogre::Vector3& b);
void vectorToPolar(const Ogre::Vector3 vec, PolarCoordinates&);
Ogre::Vector3 vectorFromTumbleDirection(Ogre::Vector3 playerPos, TUMBLE_DIRECTION direction);
PolarCoordinates polarFromStarting(Ogre::Real r, unsigned laneIdx);

Ogre::Real radiusFromVector(const Ogre::Vector3& pos);
Ogre::Real thetaFromVector(const Ogre::Vector3& pos);
