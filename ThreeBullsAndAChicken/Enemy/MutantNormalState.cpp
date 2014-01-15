#include "stdafx.h"
#include "MutantNormalState.h"
#include "../GameLevels/MainUpdate.h"


MutantNormalState::MutantNormalState()
{
}


MutantNormalState::~MutantNormalState()
{
}
void MutantNormalState::update(MutantModelHandler* enemyModel)
{
	enemyModel->normalWalk(0.2*MainUpdate::getSingletonPtr()->getDeltaTime(),NormalDirection::Left);
	UnitCircleMovement::normalSetDirection(enemyModel->getNode(), enemyModel->getNormalPos(),NormalDirection::Left);
}