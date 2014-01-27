#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "../Enemy/EnemyHandler.h"
#include "../OgreCore/OISCore.h"
#include "PlayerStats.h"
#include "../Enemy/MutantGlobalStats.h"
PlayerSelectionState::PlayerSelectionState() 
: PlayerState(PLAYER_STATES::PlayerSelectionState)
{
}
PlayerSelectionState::~PlayerSelectionState()
{
}
void PlayerSelectionState::update(PlayerModelHandler& playerModel)
{
}