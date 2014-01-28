#include "stdafx.h"
#include "MutantNormalState.h"
#include "../GameLevels/MainUpdate.h"
#include "MutantGlobalStats.h"

MutantNormalState::MutantNormalState() : BehaviourState(BEHAVOUR_STATE::NORMAL)
{
}


MutantNormalState::~MutantNormalState()
{
}
void MutantNormalState::update(UniversalModelHandler& enemyModel)
{
	auto walkSpeed = MutantGlobalStats::getSingletonPtr()->getWalkSpeed();
	enemyModel.normalWalk(walkSpeed*MainUpdate::getSingletonPtr()->getDeltaTime(),NormalDirection::Left);
	UnitCircleMovement::normalSetDirection(enemyModel.getNode(), enemyModel.getNormalPos(),NormalDirection::Left);
}