#pragma once
namespace ParticleUniverse
{
	class BaseCollider;
	class ParticleAffector;
	class ParticleEmitter;
}
class BehaviourObject;
class BeamWeaponHitTest
{
public:
	static bool hitTest(ParticleUniverse::BaseCollider* m_planeCollider, ParticleUniverse::ParticleAffector* m_collisionObserver
		, ParticleUniverse::ParticleEmitter* m_emitter, Ogre::Node* m_node, int damage, const Ogre::Real& rayHeight, const Ogre::Real& mainMassZPos);
private:
	static bool isInFrontOfBall(const Ogre::Real&, const Ogre::Real& mainMassZPos);
	static bool didItHit(const Ogre::Real&, ParticleUniverse::BaseCollider* m_planeCollider, ParticleUniverse::ParticleAffector* m_collisionObserver);
	static bool rayCastTarget(const BehaviourObject* obj, Ogre::Node* m_node, const Ogre::Real& rayHeight);
};