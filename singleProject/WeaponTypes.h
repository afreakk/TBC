#pragma once
#include "Weapon.h"
class ModelHandler;
namespace Ogre
{
	class SceneNode;
}
namespace ParticleUniverse
{
	class PlaneCollider;
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
	ParticleUniverse::PlaneCollider* m_planeCollider;

};