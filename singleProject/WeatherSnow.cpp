#include "stdafx.h"
#include "WeatherSnow.h"
#include "OgreCore.h"
#include "Player.h"
#include "PlayerContainer.h"
#include "LaneSettings.h"
#include "ParticleUniverseSystem.h"
#include "ParticleUniverseSystemManager.h"
#include "GlobalVariables.h"

template<> SnowInstance* Ogre::Singleton<SnowInstance>::msSingleton = 0;
SnowInstance::SnowInstance()
: m_systemCount(0)
{
}
SnowInstance::~SnowInstance()
{
	for (auto& it : m_particleSystems)
		ParticleUniverse::ParticleSystemManager::getSingleton().destroyParticleSystem(it.second, OgreCore::getSingleton().getSceneMgr() );
}
unsigned SnowInstance::getId()
{
	for (auto& it : m_leased)
	{
		if (!it.second)
			return it.first;
	}
	return _createSystem();
}
void SnowInstance::update()
{
	for (auto& it : m_particleSystems)
		it.second->setScaleTime(GlobalVariables::getSingleton().getSpeed());
}
int SnowInstance::_createSystem()
{
	m_particleSystems[m_systemCount] =
		ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem("snow"+boost::lexical_cast<string>(m_systemCount),"snow", OgreCore::getSingleton().getSceneMgr());
	m_particleSystems[m_systemCount]->start();
	return m_systemCount++;
}
ParticleUniverse::ParticleSystem* SnowInstance::getSystem(unsigned id)
{
	m_leased[id] = true;
	return m_particleSystems[id];
}
void SnowInstance::returnSystem(unsigned id)
{
	m_leased[id] = false;
}


WeatherSnow::WeatherSnow(const Ogre::Real& theta, const Ogre::Real& increment) 
: m_height(0.0f)
, m_theta(theta)
, m_increment(increment)
, m_activated(false)
, m_node(OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode())
{
	m_node->rotate(Vector3::UNIT_Y,Radian(m_theta));
	Vector3 snowPos = LaneSettings::getSingleton().getVectorOf(1, m_theta, m_height);
	m_node->setPosition(snowPos);
}


WeatherSnow::~WeatherSnow()
{
}

void WeatherSnow::snowCulling()
{ 
	if (float_compare(m_theta, PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta, m_increment*4.0f))
	{
		if (!m_activated)
		{
            m_activated = true;
			m_systemId = SnowInstance::getSingleton().getId();
			m_node->attachObject(SnowInstance::getSingleton().getSystem(m_systemId));
		}
	}
	else if (m_activated)
	{
		m_activated = false;
		m_node->detachObject(SnowInstance::getSingleton().getSystem(m_systemId));
		SnowInstance::getSingleton().returnSystem(m_systemId);
	}

}