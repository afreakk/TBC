#include "stdafx.h"
#include "LERPWalkAttack.h"
#include "ModelHandler.h"

LerpTowardsReturn LERPWalkAttack::update(ModelHandler& modelHandler, const Vector3& targetPos, const Ogre::Real& speed)
{
    m_lerpValue = lerpTowardsTarget(modelHandler, m_lerpValue, targetPos, speed);
	return m_lerpValue;
}
LerpTowardsReturn LERPWalkAttack::lerpTowardsTarget(ModelHandler& modelHandler, LerpTowardsReturn oldEnumValue, const Vector3& tPos, const Ogre::Real& speed)
{
    if (oldEnumValue == LerpTowardsReturn::RUNNING)
    {
        if (modelHandler.lerpWalk(tPos, speed))
            return LerpTowardsReturn::RUNNING;
        else
            return LerpTowardsReturn::ATTACKING;
    }
    else
    {
        switch (modelHandler.lerpAttack(tPos, speed))
        {
        case AttackReturn::NOT_KILLED:
            return LerpTowardsReturn::ATTACKING;
        case AttackReturn::KILLED:
            return LerpTowardsReturn::HIT;
        case AttackReturn::ANIM_ENDED:
            return LerpTowardsReturn::ANIMATION_END;
        default:
            assert(0);
            return LerpTowardsReturn::ANIMATION_END;
        }
    }
}