#pragma once
#include "ParticleEffect.h"
class SnowInstance : public Ogre::Singleton<SnowInstance>
{
public:
	SnowInstance();
	~SnowInstance();
	unsigned getId();
	ParticleUniverse::ParticleSystem* getSystem(unsigned id);
	void returnSystem(unsigned id);
	void update();
private:
	std::map<unsigned, ParticleUniverse::ParticleSystem*> m_particleSystems;
	std::map<unsigned, bool> m_leased;
	unsigned m_systemCount;

	int _createSystem();
};
class WeatherSnow 
{
public:
	WeatherSnow(const Ogre::Real& theta, const Ogre::Real& increment);
	~WeatherSnow();
	void snowCulling();
private:
	Ogre::Real m_height;
	Ogre::Real m_theta;
	Ogre::Real m_increment;
	bool m_activated;
	Ogre::SceneNode* m_node;
	unsigned m_systemId;
};

