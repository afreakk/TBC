#include "stdafx.h"
#include "MutantDeadState.h"
#include "../GameLevels/MainUpdate.h"

MutantDeadState::MutantDeadState() :BehaviourState(BEHAVOUR_STATE::DEAD)
{
}


MutantDeadState::~MutantDeadState()
{
}

void MutantDeadState::update(UniversalModelHandler& mutantModel)
{
	cout << "dead" << endl;
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	mutantModel.fallAndDie(dt);
}
