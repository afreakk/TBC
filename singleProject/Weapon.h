#pragma once
#include "ParticleEffect.h"
#include "ModelHandler.h"
enum class WeaponType
{
    LAZER,
    FLAMETHROWER,
    FIREBALL,
    SUICIDE_BOMB,
    FROSTBOLT,
    NOTHING
};
namespace ParticleUniverse
{
	class ParticleEmitter;
}

class WeaponBase : public ParticleEffect
{
public:
	WeaponBase(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName="");
	virtual ~WeaponBase();
	static WeaponType weaponTypeFromString(String weaponString);
protected:
	static int m_weaponCount;
	ModelHandler* m_model;
	ParticleUniverse::ParticleEmitter* m_emitter;
};

class WeaponMissile : public WeaponBase
{
public:
	WeaponMissile(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName);
	virtual ~WeaponMissile();
	virtual void update() override;
protected:
	Ogre::Real m_height;
};
#include "SimpleShadow.h"
class WeaponBall : public WeaponBase
{
public:
	WeaponBall(SceneNode* parentNode, ModelHandler* model, String id, String templateName, String emitterName);
	virtual ~WeaponBall();
	virtual void update() override;
	virtual void activate() override;
	virtual void stop() override;
protected:
	Ogre::Real m_ballDamageRadius;
	Ogre::Vector3 m_startingPos;
	SimpleShadow m_shadow;

	bool hitTest();
};
class WeaponBomb : public WeaponBase
{
public:
	WeaponBomb(SceneNode* parentNode, ModelHandler* model, String id, String templateName);
	virtual ~WeaponBomb();
	virtual void update() override;
};