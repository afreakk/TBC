#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerNormalTranslator.h"
class PlayerNormalState:public PlayerState
{
public:
	PlayerNormalState();
	void update(PlayerModelHandler& playerModel) override;
	~PlayerNormalState();
private:
	void handleDirection(NormalDirection activeDirection);
	NormalDirection getDirection();
	void handleBlock(PlayerModelHandler& modelHandler);

	NormalDirection m_direction;
	PlayerNormalTranslator m_translator;

};

