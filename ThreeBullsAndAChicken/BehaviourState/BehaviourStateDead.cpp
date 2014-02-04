#include "stdafx.h"
#include "BehaviourStateDead.h"
#include "../GameLevels/MainUpdate.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"
BehaviourStateDead::BehaviourStateDead() :BehaviourState(BEHAVOUR_STATE::DEAD)
{
}


BehaviourStateDead::~BehaviourStateDead()
{
}

void BehaviourStateDead::update(ModelHandler& mutantModel)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	static_cast<ModelHandlerMutant&>(mutantModel).damage();
	mutantModel.fallAndDie(dt);
}
