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
    m_node->attachObject(m_particleSystem);
	m_particleSystem->prepare();
	m_particleSystem->setRenderQueueGroup(RENDER_QUEUE_9);
}
ParticleEffect::~ParticleEffect()
{
	stop(true);
	destroyThis();
}
void ParticleEffect::stop(bool brute)
{
	if (brute)
        m_particleSystem->stop();
	else
        m_particleSystem->stopFade();
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
            ParticleReferenceContainer::getSingleton().addParticle(this);
            m_added = true;
        }
	}
	else
	{
        if (m_added)
        {
            ParticleReferenceContainer::getSingleton().removeParticle(this);
            m_added = false;
        }
	}
}