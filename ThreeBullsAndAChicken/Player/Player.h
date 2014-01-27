#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerModelHandler.h"
#include "PlayerStateSubscriber.h"
class Player
{
public:
	Player();
	~Player();
	void update();
	PLAYER_STATES getState();
	void setState(PlayerState* newState);
	void setState(PLAYER_STATES newState);
	SceneNode* getNode() const ;
	PolarCoordinates getNormalPosition() ;
	void notifySubscribers();
	void addSubsriber(PlayerStateSubscriber*, string);
	void removeSubscriber(string);
	PlayerModelHandler& getModelHandler()
	{
		return m_model;
	}
private:
	PlayerModelHandler m_model;
	unique_ptr<PlayerState> m_currentState;
	std::map <string, PlayerStateSubscriber*> m_stateSubsribers;


};

