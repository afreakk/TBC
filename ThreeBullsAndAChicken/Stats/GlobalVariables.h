#pragma once
#include "stdafx.h"
class GlobalVariables: public Singleton<GlobalVariables>
{
public:
	GlobalVariables()
		: m_speed(1.0)
	{}
	~GlobalVariables()
	{}
	const Real& getSpeed() const
	{
		return m_speed;
	}
	void setSpeed(const Real& newSpeed)
	{
		m_speed = newSpeed;
	}
private:
	Real m_speed;

};

template<> GlobalVariables* Ogre::Singleton<GlobalVariables>::msSingleton = 0;