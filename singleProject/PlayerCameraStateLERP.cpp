#include "stdafx.h"
#include "PlayerCameraStateLERP.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "PlayerCameraVars.h"
#include "PlayerContainer.h"
#include "Player.h"
PlayerCameraStateLERP::PlayerCameraStateLERP(SceneNode* playerNode) 
: m_playerNode(playerNode)
, m_lerp(0.0)
, m_r(0.0)
, m_distance(PlayerCameraVars::getSingleton().getPlayerCameraLERP().distance)
, m_height(PlayerCameraVars::getSingleton().getPlayerCameraLERP().height)
, m_spinSpeed(PlayerCameraVars::getSingleton().getPlayerCameraLERP().spinSpeed)
{
}


PlayerCameraStateLERP::~PlayerCameraStateLERP()
{
}
#include "LaneSettings.h"
void PlayerCameraStateLERP::update()
{
	m_camera->lookAt(getTiltedLerpedPlayerPos(MainUpdate::getSingleton().getScaledDeltaTime()));
}
