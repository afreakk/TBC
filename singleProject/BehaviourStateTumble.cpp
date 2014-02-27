#include "stdafx.h"
#include "BehaviourStateTumble.h"
#include "MainUpdate.h"
#include "ModelHandler.h"

BehaviourStateTumble::BehaviourStateTumble(Vector3 tumbleToPos, Real speed)
: BehaviourState(BEHAVOUR_STATE::TUMBLE)
, m_tumbleToPos(tumbleToPos)
, m_speed(speed)
, m_reachedEnd(false)
{
}


BehaviourStateTumble::~BehaviourStateTumble()
{
}

void BehaviourStateTumble::update(ModelHandler& modelHandler)
{
	m_reachedEnd = modelHandler.tumble(m_tumbleToPos,m_speed);
}

bool BehaviourStateTumble::hasReachedEnd() const 
{
    return m_reachedEnd;
}