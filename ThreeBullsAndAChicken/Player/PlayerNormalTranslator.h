#pragma once
#include "stdafx.h"
#include "PlayerModelHandler.h"
#include "../Other/UnitCircleMovement.h"
class PlayerNormalTranslator
{
public:
	PlayerNormalTranslator();
	~PlayerNormalTranslator();
	void update(PlayerModelHandler& playerModel, NormalDirection activeDirection);
private:
	void handleVelocity(NormalDirection activeDirection);
	void increaseVelocity(const Real& ammount);

	Real m_velocity;
	Real m_speed;
};

