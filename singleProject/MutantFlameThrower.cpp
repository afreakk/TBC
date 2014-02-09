#include "stdafx.h"
#include "MutantFlameThrower.h"
#include "OgreCore.h"

int MutantFlameThrower::m_flameThrowerCount = 0;
MutantFlameThrower::MutantFlameThrower(SceneNode* parentNode, ModelHandler* model)
: ParticleEffect(parentNode, ++m_flameThrowerCount, "flameThrower", "mutantflamethrower", OgreCore::getSingleton().getSceneMgr())
, m_model(model)
, m_emitter(m_particleSystem->getTechnique(0)->getEmitter("FlameEmitter"))
{
}
MutantFlameThrower::~MutantFlameThrower()
{
}

void MutantFlameThrower::update()
{
	m_emitter->position = m_model->getBonePos();
	ParticleEffect::update();
}