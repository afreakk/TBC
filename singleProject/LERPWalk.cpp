#include "stdafx.h"
#include "LERPWalk.h"
#include "ModelHandler.h"

LerpTowardsReturn LERPWalk::update(ModelHandler& modelHandler, const Vector3& targetPos, const Ogre::Real& speed)
{
    return lerpTowardsTarget(modelHandler, targetPos, speed);
}
LerpTowardsReturn LERPWalk::lerpTowardsTarget(ModelHandler& modelHandler, const Vector3& tPos, const Ogre::Real& speed)
{
    if (modelHandler.lerpWalk(tPos, speed,true))
        return LerpTowardsReturn::RUNNING;
    else
        return LerpTowardsReturn::ANIMATION_END;
}