#pragma once
#include "stdafx.h"
#include "ConfigScriptLoader.h"
//todo this should be in UniversalGameObjects
class Global
{
public:
	Global()
	{

	}
	void initLanes()
	{
		ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "globalLanes");
		m_laneCount = rootNode->findChild("laneCount")->getValueU(0);
		m_increment = rootNode->findChild("laneIncrement")->getValueR(0);
		m_firstLane = rootNode->findChild("firstLane")->getValueR(0);
		m_height = rootNode->findChild("laneHeight")->getValueR(0);
		m_laneArray = new Real[m_laneCount];
		for (unsigned i = 0; i < m_laneCount; i++)
			m_laneArray[i] = m_firstLane + m_increment*i;
	}
	Real getLane(unsigned index)
	{
		return m_laneArray[index];
	}
	Real getIncrement()
	{
		return m_increment;
	}
	Real getHeight()
	{
		return m_height;
	}
	unsigned getLaneCount()
	{
		return m_laneCount;
	}
private:
	unsigned m_laneCount;
	Real m_increment;
	Real m_firstLane;
	Real* m_laneArray;
	Real m_height;

};
extern Global g;

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
inline PolarCoordinates polarFromStarting(Real r, unsigned laneIdx)
{
	return PolarCoordinates(r, g.getLane(laneIdx), g.getHeight());
}