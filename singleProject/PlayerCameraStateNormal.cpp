#include "stdafx.h"
#include "PlayerCameraStateNormal.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "PlayerCameraVars.h"
#include "LaneSettings.h"
#include "Player.h"
#include "MainUpdate.h"
PlayerCameraStateNormal::PlayerCameraStateNormal(Player* player)
: m_player(player)
, m_distance(PlayerCameraVars::getSingleton().getPlayerCameraNormal().distance)
, m_height(PlayerCameraVars::getSingleton().getPlayerCameraNormal().height)
, m_lerp(0.0)
{
}


PlayerCameraStateNormal::~PlayerCameraStateNormal()
{
}
void PlayerCameraStateNormal::update()
{
    const Ogre::Real& dt = MainUpdate::getSingleton().getDeltaTime();
	if (m_lerp < 1.0)
		m_lerp += dt;
	setCameraPos(m_height, m_distance);
	m_camera->lookAt(getTiltedLerpedPlayerPos(dt));
}

