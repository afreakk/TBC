#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../UniversalGameObjects/UniversalModelHandler.h"
class BehaviourStateNormalTranslator
{
public:
	BehaviourStateNormalTranslator(const Real* speed);
	~BehaviourStateNormalTranslator();
	void update(UniversalModelHandler& playerModel, NormalDirection activeDirection);
private:
	void handleVelocity(NormalDirection activeDirection);
	void increaseVelocity(const Real& ammount);

	const Real& m_speed;
	Real m_velocity;
};

