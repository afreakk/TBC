#include "stdafx.h"
#include "BloodSplat.h"
#include "../OgreCore/OgreCore.h"
#include "ParticleEmitters/ParticleUniverseLineEmitter.h"
int BloodSplat::m_bloodSplatCount = 0;
BloodSplat::BloodSplat(SceneNode* parentNode)
: m_id(++m_bloodSplatCount)
, m_node(parentNode->createChildSceneNode())
, m_particleSystem( ParticleUniverse::ParticleSystemManager::getSingleton().createParticleSystem(
"bloodSpray"+boost::lexical_cast<string>(m_id), "hhStrike", OgreCore::getSingleton().getSceneMgr() ) )
, m_ran(false)
{
	m_node->attachObject(m_particleSystem);
	m_node->setPosition(0.0, 100.0, 0.0);
}


BloodSplat::~BloodSplat()
{
}

void BloodSplat::activate(Real timeScale, Vector3 direction)
{
	auto collider = m_particleSystem->getTechnique(0)->getAffector("planecollider");
	collider->position = Vector3(0.0, -100.0, 0.0);
	auto emitter = m_particleSystem->getTechnique(0)->getEmitter("bloodemitter");
	emitter->direction = direction;
	m_particleSystem->setScaleTime(timeScale);
	if (!m_ran)
	{
		m_particleSystem->start();
		m_ran = true;
	}
}