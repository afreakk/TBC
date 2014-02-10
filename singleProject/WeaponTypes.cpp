#include "stdafx.h"
#include "WeaponTypes.h"
#include "ParticleAffectors/ParticleUniversePlaneCollider.h"
#include "ParticleUniverseSystem.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "TBCRay.h"
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
{
	m_planeCollider = static_cast<ParticleUniverse::PlaneCollider*>(m_particleSystem->getTechnique(0)->getAffector("planecollider"));
    m_planeCollider->setNormal(Vector3(0.0, 0.0, 1.0));
}
void MutantFireBall::update()
{
	Vector3 height(0.0, 0.0, 0.0);
	Vector3 result;
	if (TBCRay::getSingleton().RaycastFromPoint(m_node->_getDerivedPosition() + height
		, m_node->convertLocalToWorldPosition(Vector3(0.0, 0.0, -1000.0)) - m_node->_getDerivedPosition() + height, result))
	{
        m_planeCollider->position.z = m_node->convertWorldToLocalPosition( result ).z ;
	}
	else
	{
		m_planeCollider->position.z = -4000.0;
	}
	WeaponBeam::update();
}