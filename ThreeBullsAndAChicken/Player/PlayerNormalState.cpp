#include "stdafx.h"
#include "PlayerNormalState.h"
#include "../OgreCore/OISCore.h"
#include "../GameLevels/MainUpdate.h"

PlayerNormalState::PlayerNormalState():PlayerState(PLAYER_STATES::PlayerNormalState), m_direction(NormalDirection::Right)
{
	cout << "normalState init" << endl;
}
PlayerNormalState::~PlayerNormalState()
{
	cout << "normalState destrucotr" << endl;
}
void PlayerNormalState::update(PlayerModelHandler& playerModel)
{
	auto activeDirection = getDirection();
	handleDirection(activeDirection);
	handleBlock(playerModel);
	m_translator.update(playerModel, activeDirection);
}
void PlayerNormalState::handleDirection(NormalDirection activeDirection)
{
	if (activeDirection != NormalDirection::None)
		m_direction = activeDirection;
}
void PlayerNormalState::handleBlock(PlayerModelHandler& modelHandler)
{
	auto dt = MainUpdate::getSingleton().getDeltaTime();
	auto keyboard = OISCore::getSingletonPtr()->getKeyboard();
	if (keyboard->isKeyDown(OIS::KeyCode::KC_LCONTROL))
		modelHandler.block(dt);
	else
		modelHandler.unBlock();

}
NormalDirection PlayerNormalState::getDirection()
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
