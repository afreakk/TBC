#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "../OgreCore/OISCore.h"
#include "../Enemy/MutantGlobalStats.h"
PlayerSelectionState::PlayerSelectionState() 
: BehaviourState(BEHAVOUR_STATE::SELECTION)
{
}
PlayerSelectionState::~PlayerSelectionState()
{
}
void PlayerSelectionState::update(UniversalModelHandler& playerModel)
{
}