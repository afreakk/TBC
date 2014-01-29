#include "stdafx.h"
#include "BehaviourStateDead.h"
#include "../GameLevels/MainUpdate.h"

BehaviourStateDead::BehaviourStateDead() :BehaviourState(BEHAVOUR_STATE::DEAD)
{
}


BehaviourStateDead::~BehaviourStateDead()
{
}

void BehaviourStateDead::update(UniversalModelHandler& mutantModel)
{
	cout << "dead" << endl;
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	mutantModel.fallAndDie(dt);
}
