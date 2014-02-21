#include "stdafx.h"
#include "BehaviourStateLERP.h"
#include "MainUpdate.h"
#include "ModelHandler.h"
#include "BehaviourObject.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "PlayerHandler.h"

BehaviourStateLERP::BehaviourStateLERP(BehaviourObject* target, const Real* speed, LERPBase* mode, Ogre::Vector3* targetPosition) 
: BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpReturn(LerpTowardsReturn::RUNNING)
, m_target(target)
, m_targetPos(targetPosition) // optional
, m_speed(*speed)
, m_goNextTarget(false)
, m_killed(false)
, m_lerpMode(mode)
{
	assert(m_target||targetPosition);
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
	/*if ((!m_targetPos && !m_target) || !m_targetPos &&
		(m_target->isDead() && ( m_lerpReturn == LerpTowardsReturn::RUNNING || m_lerpReturn == LerpTowardsReturn::ATTACKING )))
	{
		const std::string& name = modelHandler.getNode()->getName();
		switch (modelHandler.getType())
		{
		case ModelHandlerType::Mutant:
			MutantContainer::getSingleton().getHandler( name )->queSwitchState(MUTANT_HANDLER_STATE::NORMAL);
			return;
		case ModelHandlerType::Player:
			PlayerContainer::getSingleton().getHandler()->queSwitchState(PLAYER_HANDLER_STATE::NORMAL);
			return;
		default:
			assert(0);
			return;
		}
	}*/
	m_lerpReturn = m_lerpMode->update(modelHandler, (m_targetPos ? *m_targetPos : m_target->getNode()->getPosition()), m_speed);
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
