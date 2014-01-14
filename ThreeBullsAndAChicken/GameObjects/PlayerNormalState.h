#pragma once
#include "PlayerState.h"
#include "OISKeyboard.h"
#include "PlayerNormalTranslator.h"
class PlayerNormalState:public PlayerState
{
public:
	PlayerNormalState();
	void init() override;
	void exit() override;
	void update(PlayerModelHandler& playerModel) override;
	~PlayerNormalState();
private:
	void handleDirection(NormPDir activeDirection);
	NormPDir handleInput();
	NormPDir m_direction;
	PlayerNormalTranslator m_translator;

};

