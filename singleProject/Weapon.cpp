#include "stdafx.h"
#include "Weapon.h"
#include "OgreCore.h"
#include "ParticleUniverseSystem.h"
#include "MainUpdate.h"

#include "DetonateWeaponHitTest.h"
#include "PlayerGlobalStats.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"
const Real LaunchHeight = 100.0f;

//WeaponBase

int WeaponBase::m_weaponCount = 0;
WeaponBase::WeaponBase(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName)
: ParticleEffect(parentNode, ++m_weaponCount, id, templateName, OgreCore::getSingleton().getSceneMgr())
, m_model(model)
, m_emitter(emitterName!="" ? m_particleSystem->getTechnique(0)->getEmitter(emitterName) : nullptr)
{

}
WeaponBase::~WeaponBase()
{

}
WeaponType WeaponBase::weaponTypeFromString(String weaponString)
{
	if (weaponString == "lazer")
		return WeaponType::LAZER;
	if (weaponString == "flame")
		return WeaponType::FLAMETHROWER;
	if (weaponString == "fireball")
		return WeaponType::FIREBALL;
	if (weaponString == "suicide")
		return WeaponType::SUICIDE_BOMB;
	if (weaponString == "frostbolt")
		return WeaponType::FROSTBOLT;
	assert(0);
	return WeaponType::NOTHING;
}

//WeaponMissile

WeaponMissile::WeaponMissile(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName)
: WeaponBase(parentNode, model, id, templateName, emitterName)
, m_height(LaunchHeight)
{
	m_emitter->position.y = m_height;
}
WeaponMissile::~WeaponMissile()
{
}

void WeaponMissile::update()
{
	WeaponBase::update();
}


WeaponBomb::WeaponBomb(SceneNode* parentNode, ModelHandler* model, String id, String templateName)
: WeaponBase(parentNode, model, id, templateName)
{
}
WeaponBomb::~WeaponBomb()
{
}

void WeaponBomb::update()
{
	WeaponBase::update();
}

//WeaponBall

WeaponBall::WeaponBall(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName)
: WeaponBase(parentNode, model, id, templateName, emitterName)
, m_ballDamageRadius(200.0f)
, m_detonation(0.0f, false, false)
, m_startingPos(0.0f,LaunchHeight,0.0f)
, m_shadow(m_node)
{
	m_shadow.create();
	m_shadow.setVisible(false);
	m_shadow.setPosition(Vector3(0.0f, -LaunchHeight, 0.0f));
	m_node->setPosition(m_startingPos);
}
WeaponBall::~WeaponBall()
{
}

void WeaponBall::activate()
{
	m_detonation.stopped = false;
	m_shadow.setVisible(true);
	m_node->setPosition(m_startingPos);
	WeaponBase::activate();
}
void WeaponBall::update()
{
	if (!m_detonation.stopped)
	{
        m_node->translate(Vector3(0.0f, 0.0f, -MainUpdate::getSingleton().getDeltaTime()*1000.0f));
		if (DetonateWeaponHitTest::detonate(m_node, m_ballDamageRadius, true) && m_detonation.timer == false)
			m_detonation.timerStarted = true;
		if (m_detonation.timerStarted)
		{
			m_detonation.timer += MainUpdate::getSingleton().getScaledDeltaTime();
			if (m_detonation.timer > 0.2f)
			{
                m_particleSystem->stopFade();
				m_detonation.timer = 0.0f;
				m_detonation.timerStarted = false;
				m_detonation.stopped = true;
			}
		}
	}
	WeaponBase::update();
}
void WeaponBall::stop(bool v)
{
	m_shadow.setVisible(false);
	WeaponBase::stop(v);
}