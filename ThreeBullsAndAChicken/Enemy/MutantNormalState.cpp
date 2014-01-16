#include "stdafx.h"
#include "MutantNormalState.h"
#include "../GameLevels/MainUpdate.h"


MutantNormalState::MutantNormalState() :m_speed(0.05), MutantState(MUTANT_STATES::STATE_NORMAL)
{
}


MutantNormalState::~MutantNormalState()
{
}
void MutantNormalState::update(MutantModelHandler* enemyModel)
{
	enemyModel->normalWalk(m_speed*MainUpdate::getSingletonPtr()->getDeltaTime(),NormalDirection::Left);
	UnitCircleMovement::normalSetDirection(enemyModel->getNode(), enemyModel->getNormalPos(),NormalDirection::Left);
}