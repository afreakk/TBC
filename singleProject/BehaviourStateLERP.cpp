#include "stdafx.h"
#include "BehaviourStateLERP.h"
#include "MainUpdate.h"
#include "ModelHandler.h"
BehaviourStateLERP::BehaviourStateLERP(SceneNode* target, const Real* speed) 
: BehaviourState(BEHAVOUR_STATE::LERP)
, m_lerpState(LERP_STATE::LERP_WALK)
, m_target(target)
, m_speed(*speed)
, m_goNextTarget(false)
, m_running(true)
, m_killed(false)
{
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
	if (attackEnemy(modelHandler))
		m_goNextTarget = true;
}
bool BehaviourStateLERP::attackEnemy(ModelHandler& modelHandler)
{
	const Ogre::Vector3& tPos = m_target->getPosition();
	if (m_running)
		m_running = modelHandler.lerpWalk(tPos, m_speed);
	else
	{
		AttackReturn m = modelHandler.lerpAttack(tPos, m_speed);
		switch (m)
		{
		case AttackReturn::KILLED:
			m_killed = true;
			break;
		case AttackReturn::ANIM_ENDED:
			return true;
			break;
		}
	}


	return false;
}

void BehaviourStateLERP::attack()
{

}