#include "stdafx.h"
#include "BloodSplat.h"
#include "../OgreCore/OgreCore.h"

int BloodSplat::m_bloodSplatCount = 0;
BloodSplat::BloodSplat(SceneNode* parentNode)
: m_id(++m_bloodSplatCount)
, m_node(parentNode->createChildSceneNode())
, m_particleSystem( ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(
"bloodSpray"+boost::lexical_cast<string>(m_id), "hhStrike", OgreCore::getSingleton().getSceneMgr() ) )
, m_ran(false)
{
	m_node->attachObject(m_particleSystem);
	m_node->setPosition(0, 75, 0);
}


BloodSplat::~BloodSplat()
{
}

void BloodSplat::activate(Real timeScale)
{
	m_particleSystem->setScaleTime(timeScale);
	if (!m_ran)
	{
		m_particleSystem->start();
		m_ran = true;
	}
}