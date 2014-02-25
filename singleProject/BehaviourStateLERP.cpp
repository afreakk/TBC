#include "stdafx.h"
#include "BehaviourStateLERP.h"
#include "MainUpdate.h"
#include "ModelHandler.h"
#include "BehaviourObject.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "PlayerHandler.h"

BehaviourStateLERP::BehaviourStateLERP(BehaviourObject* target, const Real* speed, LERPBase* mode, const Ogre::Vector3& targetPosition) 
: BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpReturn(LerpTowardsReturn::RUNNING)
, m_target(target)
, m_targetPos(targetPosition) // optional
, m_speed(*speed)
, m_goNextTarget(false)
, m_killed(false)
, m_lerpMode(mode)
, m_usingTargetPosition((m_targetPos != Vector3::ZERO)?true:false)
{
	assert(m_target||m_usingTargetPosition);
	assert(!(m_target&&m_usingTargetPosition));
}

BehaviourStateLERP::~BehaviourStateLERP()
{
}

bool BehaviourStateLERP::nextTarget() const
{
	return m_goNextTarget;
}
bool BehaviourStateLERP::enemyKilled() const
{
	return m_killed;
}
void BehaviourStateLERP::update(ModelHandler& modelHandler)
{
	m_lerpReturn = m_lerpMode->update(modelHandler, (m_usingTargetPosition ? m_targetPos : m_target->getNode()->getPosition()), m_speed);
    switch (m_lerpReturn)
    {
    case LerpTowardsReturn::RUNNING:
        break;
    case LerpTowardsReturn::ATTACKING:
        break;
    case LerpTowardsReturn::HIT:
        m_killed = true;
        break;
    case LerpTowardsReturn::ANIMATION_END:
        m_goNextTarget = true;
        break;
    default:
        break;
    }
}
