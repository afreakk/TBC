#pragma once
#include "LERPBase.h"
class LERPWalk :public LERPBase
{
public:
	LerpTowardsReturn update(ModelHandler& modelHandler, const Vector3& targetPos, const Ogre::Real& speed) override;
private:
	LerpTowardsReturn lerpTowardsTarget(ModelHandler& modelHandler, const Vector3& tPos, const Ogre::Real& speed);
};

