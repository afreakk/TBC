#include "stdafx.h"
#include "BehaviourStateLERP.h"
#include "MainUpdate.h"
#include "ModelHandler.h"
#include "BehaviourObject.h"
#include "MutantContainer.h"
#include "PlayerContainer.h"
#include "PlayerHandler.h"

BehaviourStateLERP::BehaviourStateLERP(bool hit, BehaviourObject* target, const Real* speed, LERPBase* mode, const Ogre::Vector3& targetPosition) 
: BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpReturn(LerpTowardsReturn::RUNNING)
, m_target(target)
, m_targetPos(targetPosition) // optional
, m_speed(*speed)
, m_goNextTarget(false)
, m_killed(false)
, m_lerpMode(mode)
, m_usingTargetPosition((m_targetPos != Vector3::ZERO)?true:false)
, m_pause(false)
, m_hit(hit)
, m_swordSwung(false)
, m_killTimer(0.0f)
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
void BehaviourStateLERP::setPause(bool enabled)
{
	m_pause = enabled;
}
#include "SoundFactory.h"
void BehaviourStateLERP::update(ModelHandler& modelHandler)
{
	if (m_pause)
		return;
	m_lerpReturn = m_lerpMode->update(modelHandler, (m_usingTargetPosition ? m_targetPos : m_target->getNode()->getPosition()), m_speed);
    switch (m_lerpReturn)
    {
    case LerpTowardsReturn::RUNNING:
        break;
    case LerpTowardsReturn::ATTACKING:
		if (!m_swordSwung)
		{
			if (m_hit)
				SoundFactory::getSingleton().playSound("sfx/sverd/sverd_treff.ogg","sfx/sverd/sverd_treff.ogg");
			else
				SoundFactory::getSingleton().playSound("sfx/sverd/sverd_bom.ogg","sfx/sverd/sverd_bom.ogg");
			m_swordSwung = true;
		}
        break;
    case LerpTowardsReturn::HIT:
		m_killTimer += MainUpdate::getSingleton().getScaledDeltaTime();
		if (m_killTimer > 0.4f)
            m_killed = true;
        break;
    case LerpTowardsReturn::ANIMATION_END:
        m_goNextTarget = true;
        break;
    default:
        break;
    }
}
