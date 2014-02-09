#include "stdafx.h"
#include "BehaviourStateLERP.h"
#include "MainUpdate.h"
#include "ModelHandler.h"
BehaviourStateLERP::BehaviourStateLERP(SceneNode* target, const Real* speed) 
: BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpState(LERP_STATE::LERP_WALK)
, m_target(target)
, m_goNextTarget(false)
, m_speed(*speed)
{
}


BehaviourStateLERP::~BehaviourStateLERP()
{
}

bool BehaviourStateLERP::nextTarget() const
{
	return m_goNextTarget;
}
void BehaviourStateLERP::update(ModelHandler& modelHandler)
{
	if (attackEnemy(modelHandler))
		m_goNextTarget = true;
}
bool BehaviourStateLERP::attackEnemy(ModelHandler& modelHandler)
{
	const Ogre::Vector3& tPos = m_target->getPosition();
	if (m_lerpState == LERP_STATE::LERP_WALK)
		m_lerpState = modelHandler.lerpWalk(tPos, m_speed);
	else if (m_lerpState == LERP_STATE::LERP_ATTACK)
	{
		m_lerpState = modelHandler.lerpAttack(tPos, m_speed);
		if (m_lerpState == LERP_STATE::LERP_WALK)
			return true;
	}
	return false;
}
