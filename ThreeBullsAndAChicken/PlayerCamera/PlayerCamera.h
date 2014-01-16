#pragma once
#include "stdafx.h"
#include "../Camera/CameraBase.h"
#include "PlayerCameraStateNormal.h"
#include "../Player/Player.h"
class PlayerCamera:public CameraBase
{
public:
	PlayerCamera(Player* player);
	~PlayerCamera();
	void update() override;
private:
	PlayerCameraState* m_currentState;
	Player* m_player;

};

