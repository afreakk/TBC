#pragma once
#include "UnitCircleMovement.h"
#include "ModelHandler.h"
class BehaviourStateNormalTranslator
{
public:
	BehaviourStateNormalTranslator(const Real* speed);
	~BehaviourStateNormalTranslator();
	void update(ModelHandler& playerModel, NormalDirection activeDirection);
private:
	void handleVelocity(NormalDirection activeDirection);
	void increaseVelocity(const Real& ammount);

	const Real& m_speed;
	Real m_velocity;
};

