#pragma once
#include "Ogre.h"
enum class NormalDirection
{
	Left,
	Right,
	None
};
struct NormalPosition
{
	Ogre::Real r;
	Ogre::Real d;
	Ogre::Real h;
};
class UnitCircleMovement
{
public:
	static Ogre::Vector3 posFromR(NormalPosition p);
	static void normalSetPosition(Ogre::SceneNode* node, NormalPosition);
	static void normalSetDirection(Ogre::SceneNode* node, NormalPosition, NormalDirection);
};

