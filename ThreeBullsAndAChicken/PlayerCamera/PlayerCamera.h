#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "../BehaviourObject/Player.h"
#include "PlayerCameraState.h"
#include "../Templates/MessageSubscriber.h"
#include "../BehaviourObjectHandler/PlayerHandlerEnums.h"
class PlayerCamera:public MessageSubscriber<PLAYER_HANDLER_STATE>
{
public:
	PlayerCamera(Player* player);
	~PlayerCamera();
	void update();
	void notify(PLAYER_HANDLER_STATE) override;
private:
	void setNewState(PLAYER_HANDLER_STATE);

	Player* m_player;
	unique_ptr<PlayerCameraState> m_currentState;
	

};

