#include "stdafx.h"
#include "BehaviourStateTumble.h"
#include "../ModelBehaviour/ModelHandlerPlayer.h"
#include "../GameLevels/MainUpdate.h"


BehaviourStateTumble::BehaviourStateTumble(Vector3 tumbleToPos)
: BehaviourState(BEHAVOUR_STATE::TUMBLE)
, m_tumbleToPos(tumbleToPos)
, m_reachedEnd(false)
{
}


BehaviourStateTumble::~BehaviourStateTumble()
{
}

void BehaviourStateTumble::update(ModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	m_reachedEnd = static_cast<ModelHandlerPlayer&>(modelHandler).tumble(m_tumbleToPos,dt);
}