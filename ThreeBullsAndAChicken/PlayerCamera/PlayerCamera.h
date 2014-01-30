#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "../BehaviourObject/Player.h"
#include "PlayerCameraState.h"
#include "../Templates/MessageSubscriber.h"
class PlayerCamera:public MessageSubscriber<BEHAVOUR_STATE>
{
public:
	PlayerCamera(Player* player);
	~PlayerCamera();
	void update();
	void notify(BEHAVOUR_STATE) override;
private:
	void setNewState(BEHAVOUR_STATE);

	Player* m_player;
	unique_ptr<PlayerCameraState> m_currentState;
	

};

