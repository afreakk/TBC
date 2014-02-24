#include "stdafx.h"
#include "SlowMotionParticle.h"
#include "OgreCore.h"
int SlowMotionParticle::m_selectedTagCount = 0;
SlowMotionParticle::SlowMotionParticle(SceneNode* parentNode)
: m_id(++m_selectedTagCount)
, m_node(parentNode->createChildSceneNode(Vector3(0.0,100.0,0.0)))
, m_particleSystem( ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(
"slowMotionParticle"+boost::lexical_cast<string>(m_id), "slowmotion", OgreCore::getSingleton().getSceneMgr() ) )
{
	m_particleSystem->prepare();
	m_node->attachObject(m_particleSystem);
}


SlowMotionParticle::~SlowMotionParticle()
{
}

void SlowMotionParticle::select(bool enabled)
{
    if(enabled)
	    m_particleSystem->start();
	else
		m_particleSystem->stop();
}