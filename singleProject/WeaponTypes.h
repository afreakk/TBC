#pragma once
#include "Weapon.h"
#include "SimpleShadow.h"
/*
Do not use activate() for killing of entities
*/
class ModelHandler;
class BehaviourObject;
namespace Ogre
{
	class SceneNode;
}
namespace ParticleUniverse
{
	class SphereCollider;
	class OnCollisionObserver;
	class ParticleAffector;
}
//Lazer
class MutantLazer : public WeaponMissile
{
public:
	MutantLazer(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;

};
//FlameThrower
class MutantFlameThrower : public WeaponMissile
{
public:
	MutantFlameThrower(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;
};
//FireBall
class MutantFireBall : public WeaponMissile
{
public:
	MutantFireBall(Ogre::SceneNode* parentNode, ModelHandler* model);
	void activate() override;
	void update() override;
private:
	ParticleUniverse::SphereCollider* m_planeCollider;
	ParticleUniverse::ParticleAffector* m_collisionObserver;
	unsigned m_weaponDamage;
	SimpleShadow m_shadow;
	Ogre::Vector3 m_shadowPos;
	bool m_doHitTest;


	void resetShadow();
	void updateShadowPos();
	void disable();
};
//suicidebomb
class MutantSuicide : public WeaponBomb
{
public:
	MutantSuicide(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;
private:
	void detonate();
	Ogre::Real m_weaponRadius;
	bool m_detonated;
};