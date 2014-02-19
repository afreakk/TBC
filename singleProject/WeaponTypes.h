#pragma once
#include "Weapon.h"
/*
Do not use activate() for killing of entities
*/
class ModelHandler;
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
class MutantLazer : public WeaponBeam
{
public:
	MutantLazer(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;

};
//FlameThrower
class MutantFlameThrower : public WeaponBeam
{
public:
	MutantFlameThrower(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;
};
//FireBall
class MutantFireBall : public WeaponBeam
{
public:
	MutantFireBall(Ogre::SceneNode* parentNode, ModelHandler* model);
	void update() override;
private:
	ParticleUniverse::SphereCollider* m_planeCollider;
	ParticleUniverse::ParticleAffector* m_collisionObserver;
	unsigned m_weaponDamage;

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