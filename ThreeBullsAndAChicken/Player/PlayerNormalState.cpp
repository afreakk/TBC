#include "stdafx.h"
#include "PlayerNormalState.h"
#include "../OgreCore/OISCore.h"
#include "../GameLevels/MainUpdate.h"

PlayerNormalState::PlayerNormalState():PlayerState(PLAYER_STATES::PlayerNormalState), m_direction(NormalDirection::Right)
{
}
void PlayerNormalState::update(PlayerModelHandler& playerModel)
{
	auto activeDirection = handleInput();
	handleDirection(activeDirection);
	m_translator.update(playerModel, activeDirection);
}
void PlayerNormalState::handleDirection(NormalDirection activeDirection)
{
	if (activeDirection != NormalDirection::None)
		m_direction = activeDirection;
}
NormalDirection PlayerNormalState::handleInput()
{
	auto keyboard = OISCore::getSingletonPtr()->getKeyboard();

	char direction = 0;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_A))
		direction--;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_D))
		direction++;

	if (direction > 0)
		return NormalDirection::Left;
	if (direction < 0)
		return NormalDirection::Right;
	return NormalDirection::None;
}
PlayerNormalState::~PlayerNormalState()
{
}
void PlayerNormalState::init()
{
}
void PlayerNormalState::exit()
{
}