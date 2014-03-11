#include "stdafx.h"
#include "BeamWeaponHitTest.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleUniverseEmitter.h"
#include "PlayerGlobalStats.h"
#include "ModelHandlerPlayer.h"
#include "TBCRay.h"

bool BeamWeaponHitTest::hitTest(ParticleUniverse::BaseCollider* colliderObject, ParticleUniverse::ParticleAffector* collisionObserver
	, ParticleUniverse::ParticleEmitter* emitter, Ogre::Node* node, int damage, const Ogre::Real& rayHeight, const Ogre::Real& mainMassZPos)
{
	bool BeamHitSomething = false;
	colliderObject->position.y = emitter->position.y;
	colliderObject->position.x = emitter->position.x;
	std::pair<bool, Real> rayHitSomething = { false, 0.0 };
	Player* player = PlayerContainer::getSingleton().getPlayer();
	if (!static_cast<ModelHandlerPlayer&>(player->getModelHandler()).isTeleporting())
	{
        if (rayCastTarget(player,node,rayHeight))
        {
            Real zPos = node->convertWorldToLocalPosition( player->getNode()->getPosition() ).z;
            if (isInFrontOfBall(zPos,mainMassZPos))
            {
                rayHitSomething.first=true;
                rayHitSomething.second = zPos;
                if (didItHit(zPos, colliderObject, collisionObserver))
                {
                    PlayerGlobalStats::getSingleton().modifyHealth(-damage);
					BeamHitSomething = true;
                    colliderObject->position.z = rayHitSomething.second;
					return BeamHitSomething;
                }
            }
        }
	}
    for (const auto& itt : MutantContainer::getSingleton().getMutantIt())
    {
        if (itt->getNode() == (node->getParent()))
            continue;
        if (rayCastTarget(itt,node,rayHeight))
        {
			Real zPos = node->convertWorldToLocalPosition(itt->getNode()->getPosition()).z;
            if (rayHitSomething.first && rayHitSomething.second > zPos)
                continue;
			if (isInFrontOfBall(zPos,mainMassZPos))
			{
                rayHitSomething.first=true;
                rayHitSomething.second = zPos;
				if (didItHit(zPos, colliderObject, collisionObserver))
				{
                    MutantContainer::getSingleton().killMutant(itt->getNode()->getName());
					BeamHitSomething = true;
                    colliderObject->position.z = rayHitSomething.second;
					return BeamHitSomething;
				}
			}
        }

    }
	if (!rayHitSomething.first)
		colliderObject->position.z = -40000.0;
	else
		colliderObject->position.z = rayHitSomething.second;
	return BeamHitSomething;
}
bool BeamWeaponHitTest::rayCastTarget(const BehaviourObject* obj, Ogre::Node* node, const Ogre::Real& rayHeight)
{
	if (TBCRay::getSingleton().raycast(node->getParent()->getPosition() + Vector3(0.0,rayHeight,0.0), node->getParent()->getOrientation() *Vector3(0.0, 0.0, -1.0), obj))
		return true;
	return false;
}
bool BeamWeaponHitTest::isInFrontOfBall(const Ogre::Real& zPos, const Ogre::Real& mainMassZPos)
{
	if (zPos <= mainMassZPos + 100.0)
		return true;
	return false;
}
bool BeamWeaponHitTest::didItHit(const Ogre::Real& zPos, ParticleUniverse::BaseCollider* colliderObject, ParticleUniverse::ParticleAffector* collisionObserver)
{
    Real distance = Math::Abs(colliderObject->position.z - zPos);
    if (collisionObserver->isEnabled() && distance < 100.0)
    {
//        collisionObserver->setEnabled(false); thought this was necesarry but it just creates ugly behaviour on particle impact, maybe it will call kill the
        // same entity over and over becuase this is commented out
		return true;
    }
	return false;
}