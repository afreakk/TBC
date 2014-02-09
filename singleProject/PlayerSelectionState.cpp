#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "OISCore.h"
#include "MutantGlobalStats.h"
PlayerSelectionState::PlayerSelectionState() 
: BehaviourState(BEHAVOUR_STATE::SELECTION)
{
}
PlayerSelectionState::~PlayerSelectionState()
{
}
void PlayerSelectionState::update(ModelHandler& playerModel)
{
}