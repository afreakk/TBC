#include "stdafx.h"
#include "MutantFlameThrower.h"
#include "../OgreCore/OgreCore.h"

int MutantFlameThrower::m_flameThrowerCount = 0;
MutantFlameThrower::MutantFlameThrower(SceneNode* parentNode)
: m_id(++m_flameThrowerCount)
, m_node(parentNode->createChildSceneNode())
, m_particleSystem( ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(
"flameThrower"+boost::lexical_cast<string>(m_id), "mutantflamethrower", OgreCore::getSingleton().getSceneMgr() ) )
, m_ran(false)
{
	m_node->attachObject(m_particleSystem);
	m_node->setPosition(0, 75, 0);
}


MutantFlameThrower::~MutantFlameThrower()
{
}

void MutantFlameThrower::activate(Real timeScale)
{
	m_particleSystem->setScaleTime(timeScale);
	if (!m_ran)
	{
		m_particleSystem->start();
	}
}