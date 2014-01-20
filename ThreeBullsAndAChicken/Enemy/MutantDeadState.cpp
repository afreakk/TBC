#include "stdafx.h"
#include "MutantDeadState.h"
#include "../GameLevels/MainUpdate.h"

MutantDeadState::MutantDeadState() :MutantState(MUTANT_STATES::STATE_DEAD)
{
}


MutantDeadState::~MutantDeadState()
{
}

void MutantDeadState::update(MutantModelHandler* mutantModel)
{
	cout << "dead" << endl;
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	mutantModel->fallAndDie(dt);
}
void MutantDeadState::init(MutantModelHandler* mutantModel)
{

}
void MutantDeadState::exit()
{

}