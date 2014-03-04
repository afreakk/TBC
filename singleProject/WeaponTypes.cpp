#include "stdafx.h"
#include "WeaponTypes.h"
#include "ParticleAffectors/ParticleUniversePlaneCollider.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleObservers/ParticleUniverseOnCollisionObserver.h"
#include "ParticleUniverseSystem.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"
#include "TBCRay.h"
#include "MainUpdate.h"
#include "PlayerGlobalStats.h"
#include "BeamWeaponHitTest.h"
//MutantLazer
MutantLazer::MutantLazer(SceneNode* parentNode, ModelHandler* model)
: WeaponMissile(parentNode, model, "MutantLazer", "lazer", "lazerEmitter")
{
}
void MutantLazer::update()
{

	WeaponMissile::update();
}
//MutantFlameThrower
MutantFlameThrower::MutantFlameThrower(SceneNode* parentNode, ModelHandler* model)
: WeaponMissile(parentNode, model, "MutantflameThrower", "flamethrower", "FlameEmitter" )
{
}
void MutantFlameThrower::update()
{

	WeaponMissile::update();
}
FrostBolt::FrostBolt(Ogre::SceneNode* parentNode, ModelHandler* model)
:WeaponBall(parentNode, model, "MutantFrostBolt", "Flare/mp_fireball_02", "")
{
}
//MutantFireBall
MutantFireBall::MutantFireBall(SceneNode* parentNode, ModelHandler* model)
: WeaponMissile(parentNode, model, "MutantFireBall", "FireBall", "FireEmitter" )
, m_weaponDamage(40)
, m_shadow(parentNode)
, m_shadowPos(Vector3::ZERO)
, m_doHitTest(false)
{
	m_collisionObserver = static_cast<ParticleUniverse::ParticleAffector*>(m_particleSystem->getTechnique(0)->getAffector("boolman"));
	m_planeCollider = static_cast<ParticleUniverse::SphereCollider*>(m_particleSystem->getTechnique(0)->getAffector("planecollider"));
    m_shadow.create();
	m_shadow.setVisible(false);
}
void MutantFireBall::activate()
{
	resetShadow();
	m_shadow.setVisible(true);
	m_doHitTest = true;
	WeaponMissile::activate();
}
void MutantFireBall::resetShadow()
{
	m_shadowPos = Vector3::ZERO;
    m_shadow.setPosition(m_shadowPos);
}
void MutantFireBall::updateShadowPos()
{
    Ogre::Real particleVelocity = 1500.0f * m_particleSystem->getScaleTime(); // 1500 = velocity in this particular prticlesystem
    m_shadowPos.z -= particleVelocity * MainUpdate::getSingleton().getDeltaTime();
	m_shadow.setPosition(m_shadowPos);
}
void MutantFireBall::update()
{
	WeaponMissile::update();
	updateShadowPos();
	if (m_doHitTest)
	{
        if (BeamWeaponHitTest::hitTest(m_planeCollider, m_collisionObserver, m_emitter, m_node, m_weaponDamage, m_height, m_shadowPos.z))
            disable();
	}
}
void MutantFireBall::disable()
{
    m_shadow.setVisible(false);
	m_doHitTest = false;
}
void MutantFireBall::stop()
{
	disable();
	WeaponMissile::stop();
}

MutantSuicide::MutantSuicide(Ogre::SceneNode* parentNode, ModelHandler* model)
: WeaponBomb(parentNode, model, "suicideExploisionnn", "suicideExplosion" )
, m_weaponRadius(200.0)
, m_detonated(false)
{
	m_node->setPosition(0.0, 150.0, 0.0);
}
void MutantSuicide::update()
{
	WeaponBomb::update();
	if (!m_detonated)
	{
		detonate();
		m_detonated = true;
	}
}
void MutantSuicide::detonate()
{
    //player
	if (PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition().distance(m_node->getParent()->getPosition()) < m_weaponRadius)
        PlayerGlobalStats::getSingleton().modifyHealth(-50);
    //mutants
	for (auto itt : MutantContainer::getSingleton().getMutantIt())
	{
        Node* iMutantNode = itt->getNode();
        if (iMutantNode == (m_node->getParent()))
            continue;
		if (iMutantNode->getPosition().distance(m_node->getParent()->getPosition())< m_weaponRadius)
			MutantContainer::getSingleton().killMutant(itt->getNode()->getName());
    }
}
