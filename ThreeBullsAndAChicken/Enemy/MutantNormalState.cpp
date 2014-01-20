#include "stdafx.h"
#include "MutantNormalState.h"
#include "../GameLevels/MainUpdate.h"
#include "MutantGlobalStats.h"

MutantNormalState::MutantNormalState() : MutantState(MUTANT_STATES::STATE_NORMAL)
{
}


MutantNormalState::~MutantNormalState()
{
}
void MutantNormalState::init(MutantModelHandler* mutantModel)
{

}
void MutantNormalState::exit()
{

}
void MutantNormalState::update(MutantModelHandler* enemyModel)
{
	auto walkSpeed = MutantGlobalStats::getSingletonPtr()->getWalkSpeed();
	enemyModel->normalWalk(walkSpeed*MainUpdate::getSingletonPtr()->getDeltaTime(),NormalDirection::Left);
	UnitCircleMovement::normalSetDirection(enemyModel->getNode(), enemyModel->getNormalPos(),NormalDirection::Left);
}