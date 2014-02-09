#include "stdafx.h"
#include "BehaviourStateDead.h"
#include "ModelHandlerMutant.h"
#include "MainUpdate.h"
BehaviourStateDead::BehaviourStateDead() 
: BehaviourState(BEHAVOUR_STATE::DEAD)
{
}


BehaviourStateDead::~BehaviourStateDead()
{
}

void BehaviourStateDead::update(ModelHandler& modelHandler)
{
	modelHandler.fallAndDie();
}
