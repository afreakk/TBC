#include "stdafx.h"
#include "PlayerHandlerStateBlankAttack.h"
#include "BehaviourStateLERP.h"
#include "Player.h"
#include "PlayerGlobalStats.h"
#include "LERPWalkAttack.h"
#include "ModelHandler.h"
PlayerHandlerStateBlankAttack::PlayerHandlerStateBlankAttack(Player* player)
: HandlerState(PLAYER_HANDLER_STATE::BLANK_ATTACK)
, m_player(player)
{
	setState();
}
void PlayerHandlerStateBlankAttack::setState()
{
	PolarCoordinates pcoord = m_player->getPolarCoordinates();
	pcoord.theta += (m_player->getModelHandler().getNormalDirection() == NormalDirection::dirLeft ? -Math::PI / 480.0f : Math::PI / 480.0f);
	Vector3 targetPos = UnitCircleMovement::VectorFromPolar(pcoord);
	m_lerpState = unique_ptr<BehaviourStateLERP>(new BehaviourStateLERP(nullptr
		, &PlayerGlobalStats::getSingleton().getLERPSpeed_NoEnergy(), new LERPWalkAttack(), targetPos));
	m_player->setState(m_lerpState.get());
}

void PlayerHandlerStateBlankAttack::update()
{
    if (m_lerpState->nextTarget())
        m_state = PLAYER_HANDLER_STATE::NORMAL;
}
