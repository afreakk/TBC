#pragma once
enum class LerpTowardsReturn
{
    RUNNING,
    ATTACKING,
    HIT,
    ANIMATION_END
};
class ModelHandler;
class LERPBase
{
public:
	virtual ~LERPBase()
	{}
	virtual LerpTowardsReturn update(ModelHandler& modelHandler, const Vector3& targetPos, const Ogre::Real& speed)=0;
};