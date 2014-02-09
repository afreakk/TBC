#pragma once
#include "ParticleUniverseSystemManager.h"
#include "GlobalVariables.h"
#include "ParticleReferenceContainer.h"
#include "boost/noncopyable.hpp"
class ParticleEffect : public boost::noncopyable
{
public:
	ParticleEffect(SceneNode* parentNode, const int id, const Ogre::String & 	name, const Ogre::String & 	templateName, Ogre::SceneManager * 	sceneManager)
		: m_id(id)
		, m_sMgr(sceneManager)
		, m_particleSystem(ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(name + boost::lexical_cast<string>(m_id), templateName, m_sMgr))
        , m_node(parentNode->createChildSceneNode())
		, m_added(false)
	{
		m_particleSystem->prepare();
        m_node->attachObject(m_particleSystem);
	}
	~ParticleEffect()
	{
		if (m_added)
            ParticleReferenceContainer::getSingleton().removeParticle(this);
		m_particleSystem->stop();
        m_node->detachObject(m_particleSystem);
		ParticleUniverse::ParticleSystemManager::getSingleton().destroyParticleSystem(m_particleSystem, m_sMgr);
	}
	virtual void update()
	{
		m_particleSystem->setScaleTime(GlobalVariables::getSingleton().getSpeed());
	}
	virtual void activate()
	{
		if (!m_added)
		{
            ParticleReferenceContainer::getSingleton().addParticle(this);
			m_added = true;
		}
		m_particleSystem->start();
	}
	void stop()
	{
		m_particleSystem->stop();
	}
protected:
	const int m_id;
	bool m_added;
	Ogre::SceneManager* m_sMgr;
	SceneNode* m_node;
	ParticleUniverse::ParticleSystem* m_particleSystem;
};

