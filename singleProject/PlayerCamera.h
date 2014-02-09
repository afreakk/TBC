#pragma once
#include "CameraBase.h"
#include "Player.h"
#include "PlayerCameraState.h"
#include "MessageSubscriber.h"
#include "PlayerHandlerEnums.h"
#include "PlayerCameraVars.h"
class PlayerCamera:public MessageSubscriber<PLAYER_HANDLER_STATE>
{
public:
	PlayerCamera();
	void init(Player* player);
	~PlayerCamera();
	void update();
	void notify(PLAYER_HANDLER_STATE) override;
private:
	void setNewState(PLAYER_HANDLER_STATE);

	Player* m_player;
	unique_ptr<PlayerCameraState> m_currentState;
	unique_ptr<PlayerCameraVars> m_playerCameraVars;
	

};

