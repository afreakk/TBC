#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "../Player/Player.h"
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
	void setNewState(PLAYER_STATES);

	Player* m_player;
	unique_ptr<PlayerCameraState> m_currentState;
	

};

