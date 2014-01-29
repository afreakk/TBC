#include "stdafx.h"
#include "BehaviourStateLERP.h"

#include "../GameLevels/MainUpdate.h"
BehaviourStateLERP::BehaviourStateLERP(SceneNode* target) :BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpState(LERP_STATE::LERP_WALK)
, m_target(target)
, m_goNextTarget(false)
{
}


BehaviourStateLERP::~BehaviourStateLERP()
{
}

bool BehaviourStateLERP::nextTarget() const
{
	return m_goNextTarget;
}
void BehaviourStateLERP::update(UniversalModelHandler& modelHandler)
{
	if (attackEnemy(modelHandler))
		m_goNextTarget = true;

}
bool BehaviourStateLERP::attackEnemy(UniversalModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	const Ogre::Vector3& tPos = m_target->getPosition();
	if (m_lerpState == LERP_STATE::LERP_WALK)
		m_lerpState = modelHandler.lerpWalk(tPos, dt);
	else if (m_lerpState == LERP_STATE::LERP_ATTACK)
	{
		m_lerpState = modelHandler.lerpAttack(tPos, dt);
		if (m_lerpState == LERP_STATE::LERP_WALK)
		{
			return true;
		}
	}
	return false;
}
