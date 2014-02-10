#pragma once
#include "boost/noncopyable.hpp"
class ManualLine : public boost::noncopyable
{
public:
	ManualLine();
	ManualLine(Ogre::Vector3 fromPoint, Ogre::Vector3 toPoint, string material);
	void init(Ogre::Vector3 fromPoint, Ogre::Vector3 toPoint, string material);
	~ManualLine();
	void update(Ogre::Vector3 fromPoint, Ogre::Vector3 toPoint);
private:
	Ogre::ManualObject* m_line;
};