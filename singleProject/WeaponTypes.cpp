#include "stdafx.h"
#include "WeaponTypes.h"
#include "ParticleAffectors/ParticleUniversePlaneCollider.h"
#include "ParticleAffectors/ParticleUniverseSphereCollider.h"
#include "ParticleObservers/ParticleUniverseOnCollisionObserver.h"
#include "ParticleUniverseSystem.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
#include "Player.h"
#include "TBCRay.h"
static const Vector3 RayHeight(0.0, 100.0, 0.0);
//MutantLazer
MutantLazer::MutantLazer(SceneNode* parentNode, ModelHandler* model)
: WeaponBeam(parentNode, model, "MutantLazer", "lazer", "lazerEmitter")
{
}
void MutantLazer::update()
{

	WeaponBeam::update();
}
//MutantFlameThrower
MutantFlameThrower::MutantFlameThrower(SceneNode* parentNode, ModelHandler* model)
: WeaponBeam(parentNode, model, "MutantflameThrower", "flamethrower", "FlameEmitter" )
{
}
void MutantFlameThrower::update()
{

	WeaponBeam::update();
}
//MutantFireBall
MutantFireBall::MutantFireBall(SceneNode* parentNode, ModelHandler* model)
: WeaponBeam(parentNode, model, "MutantFireBall", "FireBall", "FireEmitter" )
, m_weaponDamage(40)
{
	m_collisionObserver = static_cast<ParticleUniverse::ParticleAffector*>(m_particleSystem->getTechnique(0)->getAffector("boolman"));
	m_planeCollider = static_cast<ParticleUniverse::SphereCollider*>(m_particleSystem->getTechnique(0)->getAffector("planecollider"));
}
void MutantFireBall::update()
{
	m_planeCollider->position.y = m_emitter->position.y;
	m_planeCollider->position.x = m_emitter->position.x;
	if (TBCRay::getSingleton().raycast(m_node->getParent()->getPosition()+ RayHeight
		,  m_node->getParent()->getOrientation() *Vector3(0.0, 0.0, -1.0), PlayerContainer::getSingleton().getPlayer()))
	{
        m_planeCollider->position.z = m_node->convertWorldToLocalPosition( PlayerContainer::getSingleton().getPlayer()->getNode()->getPosition() ).z ;
		if (m_collisionObserver->isEnabled())
		{
			shootPlayer(m_weaponDamage);
			m_collisionObserver->setEnabled(false);
		}
	}
	else //not hit player
	{
		bool hitMutant = false;
        for (unsigned i = 0; i < MutantContainer::getSingleton().getMutants().size(); i++)
        {
			Node* iMutantNode = MutantContainer::getSingleton().getMutants()[i]->getNode();
			if (iMutantNode == (m_node->getParent()))
				continue;
            if (TBCRay::getSingleton().raycast(m_node->getParent()->getPosition()+ RayHeight,  m_node->getParent()->getOrientation() *Vector3(0.0, 0.0, -1.0)
                , MutantContainer::getSingleton().getMutants()[i].get()))
            {
                hitMutant = true;
                m_planeCollider->position.z = m_node->convertWorldToLocalPosition( MutantContainer::getSingleton().getMutants()[i]->getNode()->getPosition() ).z ;
                if (m_collisionObserver->isEnabled())
                {
                    shootMutant(i);
                    m_collisionObserver->setEnabled(false);
					break;
                }
            }

        }
		if (!hitMutant)
            m_planeCollider->position.z = -40000.0;
	}
	WeaponBeam::update();
}