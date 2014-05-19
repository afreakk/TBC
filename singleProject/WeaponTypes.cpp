#include "stdafx.h"
#include "WeaponTypes.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleAffectors/ParticleUniverseLinearForceAffector.h"
#include "ParticleUniverseSystem.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"
#include "TBCRay.h"
#include "MainUpdate.h"
#include "PlayerGlobalStats.h"
#include "BeamWeaponHitTest.h"
#include "DetonateWeaponHitTest.h"
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
:WeaponBall(parentNode, model, "MutantFrostBolt", "frostbolt", "")
, m_lForceAffector(static_cast<ParticleUniverse::LinearForceAffector*>(m_particleSystem->getTechnique(1)->getAffector("force")))
{
//    static_cast<ParticleUniverse::LinearForceAffector*>(m_particleSystem->getTechniquedd(1)->
}
void FrostBolt::activate()
{
	WeaponBall::activate();
}
#include "MutantGlobalStats.h"
void FrostBolt::update()
{
	if (!m_detonation.deactivated)
	{
		Vector3 lforce = Vector3(0, 0, 1500);
        setForce(lforce);
	}
	else
	{
		m_lForceAffector->setEnabled(false);
	}
	WeaponBall::update();
}
void FrostBolt::setForce(const Ogre::Vector3& localForceDirection)
{
	m_lForceAffector->setForceVector(m_node->getParent()->getOrientation()*localForceDirection);
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
static int fucku = 0;
void MutantFireBall::update()
{
	WeaponMissile::update();
	updateShadowPos();
	if (m_doHitTest)
	{
		cout << fucku++ << endl;
		BeamWeaponHitTest::fireBallUpdate(m_planeCollider, m_collisionObserver, m_emitter, m_node, m_weaponDamage, m_height, m_shadowPos.z);
		if (m_collisionObserver->isEnabled())
            disable();
	}
}
void MutantFireBall::disable()
{
    m_shadow.setVisible(false);
	m_doHitTest = false;
}
void MutantFireBall::stop(bool v)
{
	disable();
	WeaponMissile::stop(v);
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
		DetonateWeaponHitTest::detonate(m_node->getParent() , m_weaponRadius);
		m_detonated = true;
	}
}
