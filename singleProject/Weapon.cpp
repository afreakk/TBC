#include "stdafx.h"
#include "Weapon.h"
#include "OgreCore.h"
#include "ParticleUniverseSystem.h"
#include "MainUpdate.h"

#include "PlayerGlobalStats.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"

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
	assert(0);
	return WeaponType::NOTHING;
}

//WeaponMissile

WeaponMissile::WeaponMissile(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName)
: WeaponBase(parentNode, model, id, templateName, emitterName)
, m_height(150.0)
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
, m_ballDamageRadius(100.0)
, m_endSpell(false)
{
}
WeaponBall::~WeaponBall()
{
}

void WeaponBall::update()
{
	if (m_endSpell)
		return;
	m_node->translate(Vector3(0.0, 0.0, -MainUpdate::getSingleton().getDeltaTime()*200.0));
	if (hitTest())
	{
        m_endSpell = true;
	}
	else if (m_node->getPosition().z < -400.0)
		m_endSpell = true;
	WeaponBase::update();
	if (m_endSpell)
	{
		m_particleSystem->stop();
	}
}
bool WeaponBall::hitTest()
{
	if (m_node->_getDerivedPosition().distance(PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition()) < m_ballDamageRadius)
		return true;
	return false;
}
