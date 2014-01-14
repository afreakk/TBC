#include "stdafx.h"
#include "PlayerNormalState.h"
#include "../OgreCore/OISCore.h"
#include "../GameLevels/MainUpdate.h"

PlayerNormalState::PlayerNormalState(): m_direction(NormPDir::Right)
{
}
void PlayerNormalState::update(PlayerModelHandler& playerModel)
{
	auto activeDirection = handleInput();
	handleDirection(activeDirection);
	m_translator.update(playerModel, activeDirection);
}
void PlayerNormalState::handleDirection(NormPDir activeDirection)
{
	if (activeDirection != NormPDir::None)
		m_direction = activeDirection;
}
NormPDir PlayerNormalState::handleInput()
{
	auto keyboard = OISCore::getSingletonPtr()->getKeyboard();

	char direction = 0;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_A))
		direction++;
	if (keyboard->isKeyDown(OIS::KeyCode::KC_D))
		direction--;

	if (direction > 0)
		return NormPDir::Left;
	if (direction < 0)
		return NormPDir::Right;
	return NormPDir::None;
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