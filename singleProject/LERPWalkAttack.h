#pragma once
#include "LERPBase.h"
class LERPWalkAttack : public LERPBase
{
public:
	LERPWalkAttack() : m_lerpValue(LerpTowardsReturn::RUNNING) {}
	LerpTowardsReturn update(ModelHandler& modelHandler, const Vector3& targetPos, const Ogre::Real& speed) override;
private:
	LerpTowardsReturn lerpTowardsTarget(ModelHandler& modelHandler, LerpTowardsReturn oldEnumValue, const Vector3& tPos, const Ogre::Real& speed);
	LerpTowardsReturn m_lerpValue;

};