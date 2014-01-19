#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "../Player/Player.h"
#include <map>
#include "../Player/PlayerStateSubscriber.h"
#include "PlayerCameraState.h"
class PlayerCamera:public PlayerStateSubscriber
{
public:
	PlayerCamera(Player* player);
	~PlayerCamera();
	void update();
	void notify(PLAYER_STATES) override;
private:
	void setNewState(PLAYER_STATES,bool);
	PLAYER_STATES m_currentState;
	std::map<PLAYER_STATES, PlayerCameraState*> m_states;
	Player* m_player;

};

