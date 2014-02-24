#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "OISCore.h"
#include "MutantGlobalStats.h"
#include "ModelHandlerPlayer.h"
PlayerSelectionState::PlayerSelectionState(ModelHandler* playerModel) 
: BehaviourState(BEHAVOUR_STATE::SELECTION)
, m_playerModel(static_cast<ModelHandlerPlayer*>(playerModel))
{
	m_playerModel->displaySlowMotionParticle(true);
}
PlayerSelectionState::~PlayerSelectionState()
{
	m_playerModel->displaySlowMotionParticle(false);
}
void PlayerSelectionState::update(ModelHandler& playerModel)
{
}