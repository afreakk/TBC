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
	m_particleSystem->setTightBoundingBox(true);
    m_node->attachObject(m_particleSystem);
}
ParticleEffect::~ParticleEffect()
{
	destroyThis();
    if (m_added)
        ParticleReferenceContainer::getSingleton().removeParticle(this);
}
void ParticleEffect::stop()
{
    m_particleSystem->stop();
    m_node->detachObject(m_particleSystem);
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
    if (!m_added)
    {
        ParticleReferenceContainer::getSingleton().addParticle(this);
        m_added = true;
    }
    m_particleSystem->start();
}
