#include "stdafx.h"
#include "LaneSettings.h"
#include "ConfigScriptLoader.h"
#include "UnitCircleMovement.h"
template<> LaneSettings* Ogre::Singleton<LaneSettings>::msSingleton = 0;
LaneSettings::LaneSettings()
{
}


LaneSettings::~LaneSettings()
{
}

unsigned LaneSettings::getClosestLane(const Ogre::Vector3& position)
{
	unsigned index = 0;
	Real radius = radiusFromVector(position);
	Real closest = 10000.0;
	for (unsigned i = 0; i < getLaneCount(); i++)
	{
		Real distanceOffset = abs(getLane(i) - radius);
		if (distanceOffset < closest)
		{
			index=i;
			closest = distanceOffset;
		}
	}
	return index;
}
unsigned LaneSettings::getClosestLane(const PolarCoordinates& pos)
{
	unsigned index = 0;
	Real radius = pos.radius;
	Real closest = 10000.0;
	for (unsigned i = 0; i < getLaneCount(); i++)
	{
		Real distanceOffset = abs(getLane(i) - radius);
		if (distanceOffset < closest)
		{
			index=i;
			closest = distanceOffset;
		}
	}
	return index;
}
Ogre::Vector3 LaneSettings::getVectorOf(unsigned index, const Ogre::Real& r, const Ogre::Real& height)
{
	Real d = getLane(index);
	return UnitCircleMovement::VectorFromPolar(PolarCoordinates(r, d, height));
}
void LaneSettings::initLanes()
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
Real LaneSettings::getLane(const unsigned index)
{
    return m_laneArray[index];
}
Real LaneSettings::getIncrement()
{
    return m_increment;
}
Real LaneSettings::getHeight()
{
    return m_height;
}
unsigned LaneSettings::getLaneCount()
{
    return m_laneCount;
}