#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "../Player/Player.h"
#include "../UniversalBehaviourState/BehaviourStateSubscriber.h"
#include "PlayerCameraState.h"
class PlayerCamera:public BehaviourStateSubscriber
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

