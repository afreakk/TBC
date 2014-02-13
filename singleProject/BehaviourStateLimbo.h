
#include "BehaviourState.h"
class BehaviourStateLimbo : public BehaviourState
{
public:
	BehaviourStateLimbo()
		: BehaviourState(BEHAVOUR_STATE::LIMBO)
	{}
	~BehaviourStateLimbo()
	{}
	virtual void update(ModelHandler&)
	{}
};