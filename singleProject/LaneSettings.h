#pragma once
#include "OgreSingleton.h"
class LaneSettings : public Ogre::Singleton<LaneSettings>
{
public:
	LaneSettings();
	~LaneSettings();
	void initLanes();
	Ogre::Real getLane(unsigned index);
	Ogre::Real getIncrement();
    Ogre::Real getHeight();
	Ogre::Vector3 getVectorOf(unsigned index, const Ogre::Real& r, const Ogre::Real& height);
	unsigned getLaneCount();
private:
	unsigned m_laneCount;
    Ogre::Real m_increment;
    Ogre::Real m_firstLane;
    Ogre::Real* m_laneArray;
    Ogre::Real m_height;

};