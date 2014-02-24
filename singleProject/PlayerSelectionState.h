#pragma once
#include "BehaviourState.h"
class ModelHandlerPlayer;
class ModelHandler;
class PlayerSelectionState:public BehaviourState
{
public:
	PlayerSelectionState(ModelHandler* playerModel);
	~PlayerSelectionState();
	void update(ModelHandler& playerModel) override;
private:
	ModelHandlerPlayer* m_playerModel;
};

