#include "stdafx.h"
#include "ParticleEffect.h"
#include "ParticleReferenceContainer.h"
#include "GlobalVariables.h"
#include "ParticleUniverseSystemManager.h"
#include "OgreCore.h"

ParticleEffect::ParticleEffect(SceneNode* parentNode, const int id, const Ogre::String & 	name, const Ogre::String & 	templateName, Ogre::SceneManager * 	sceneManager)
    : m_id(id)
    , m_sMgr(sceneManager)
    , m_particleSystem(ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(name + boost::lexical_cast<string>(m_id), templateName, m_sMgr))
    , m_node(parentNode->createChildSceneNode())
    , m_added(false)
{
	m_particleSystem->prepare();
}
ParticleEffect::~ParticleEffect()
{
	stop();
	destroyThis();
}
void ParticleEffect::stop()
{
    m_particleSystem->stop();
	setParticleSystem(false);
}

void ParticleEffect::destroyThis()
{
    ParticleUniverse::ParticleSystemManager::getSingleton().destroyParticleSystem(m_particleSystem, m_sMgr);
}
void ParticleEffect::update()
{
    m_particleSystem->setScaleTime(GlobalVariables::getSingleton().getSpeed());
}
void ParticleEffect::activate()
{
    m_particleSystem->start();
	setParticleSystem(true);
}

void ParticleEffect::setParticleSystem(bool enabled)
{
	if (enabled)
	{
        if (!m_added)
        {
            m_node->attachObject(m_particleSystem);
            ParticleReferenceContainer::getSingleton().addParticle(this);
            m_added = true;
        }
	}
	else
	{
        if (m_added)
        {
            m_node->detachObject(m_particleSystem);
            ParticleReferenceContainer::getSingleton().removeParticle(this);
            m_added = false;
        }
	}
}