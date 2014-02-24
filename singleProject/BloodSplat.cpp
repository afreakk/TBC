#include "stdafx.h"
#include "BloodSplat.h"
#include "OgreCore.h"
#include "ModelHandler.h"
#include "ParticleUniverseSystem.h"
int BloodSplat::m_bloodSplatCount = 0;
BloodSplat::BloodSplat(SceneNode* parentNode, ModelHandler* model)
: ParticleEffect(parentNode, ++m_bloodSplatCount, "bloodSpray", "hhStrike", OgreCore::getSingleton().getSceneMgr())
, m_model(model)
, m_emitter(m_particleSystem->getTechnique(0)->getEmitter("bloodemitter"))
{
	auto collider = m_particleSystem->getTechnique(0)->getAffector("planecollider");
	collider->position = Vector3(0.0, 0.0, 0.0);
}


BloodSplat::~BloodSplat()
{
}

void BloodSplat::update()
{
	m_emitter->position = m_model->getBonePos();
      
	ParticleEffect::update();
}
void BloodSplat::setDirection(Vector3 direction)
{
	m_emitter->direction = direction;

}
