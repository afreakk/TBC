#include "stdafx.h"
#include "Player.h"

#include "PlayerNormalState.h"
#include "PlayerSelectionState.h"
#include "PlayerLERPState.h"
Player::Player() : m_currentState(nullptr), m_model(PolarCoordinates(0.0,5.5,0.2))
{

	setState(PLAYER_STATES::PlayerNormalState);
//	m_model.getEntity()->setMaterialName("def");
}

Player::~Player()
{

}

void Player::setState(PlayerState* newState)
{
	m_currentState.reset();
	m_currentState = unique_ptr<PlayerState>{ newState };
	notifySubscribers();
}

void Player::setState(PLAYER_STATES newState)
{
	m_currentState.reset();
	switch (newState)
	{
	case PLAYER_STATES::PlayerNormalState:
		m_currentState = unique_ptr<PlayerState>{ new PlayerNormalState() };
		break;
	case PLAYER_STATES::PlayerSelectionState:
		m_currentState = unique_ptr<PlayerState>{ new PlayerSelectionState() };
		break;
	/*case PLAYER_STATES::PlayerLERPState:
		m_currentState = new PlayerLERPState();
		break;   does not instantiate its own lerpstate */ 
	default:
		assert(0);
		break;
	}
	notifySubscribers();
}
PLAYER_STATES Player::getState()
{
	return m_currentState->getState();
}
void Player::update()
{
	m_currentState->update(m_model);
	if (m_currentState->getNextState() != m_currentState->getState())
		setState(m_currentState->getNextState());
}
			//gets
PolarCoordinates Player::getNormalPosition() 
{
	return m_model.getNormalPos();
}
SceneNode* Player::getNode() const 
{
	return m_model.getNode();
}
void Player::addSubsriber(PlayerStateSubscriber* subscriber, string id)
{
	m_stateSubsribers[id] = subscriber;
	m_stateSubsribers[id]->notify(getState());
}
void Player::removeSubscriber(string id)
{
	m_stateSubsribers.erase(id);
}
void Player::notifySubscribers()
{
	for (auto & subsriber : m_stateSubsribers)
		subsriber.second->notify(getState());
}