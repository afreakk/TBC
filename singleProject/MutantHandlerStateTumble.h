
#pragma once
#include "HandlerState.h"
#include "ENUMTumbleDirection.h"
#include "MutantHandlerEnums.h"
class Mutant;
class BehaviourStateTumble;
class MutantHandlerStateTumble: public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateTumble(Mutant* mutant, TUMBLE_DIRECTION=TUMBLE_DIRECTION::DIRECTION_NONE);
	~MutantHandlerStateTumble();
	void update() override;
private:
	TUMBLE_DIRECTION m_direction;
	Mutant* m_mutant;
	std::unique_ptr<BehaviourStateTumble> m_currentTumbleState;

	TUMBLE_DIRECTION getTumbleDirection(Mutant* mutant);
};
