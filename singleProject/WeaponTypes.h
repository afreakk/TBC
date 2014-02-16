#pragma once
#include "Weapon.h"
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
	void activate() override;
private:
	Ogre::Real m_weaponRadius;
};