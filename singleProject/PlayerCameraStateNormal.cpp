#include "stdafx.h"
#include "PlayerCameraStateNormal.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "PlayerCameraVars.h"
#include "LaneSettings.h"
#include "Player.h"
#include "MainUpdate.h"
Ogre::Vector3 PlayerCameraStateNormal::m_lerpedPlayerPos = Vector3::ZERO;
PlayerCameraStateNormal::PlayerCameraStateNormal(Player* player) 
: m_player(player)
, m_camera(OgreCore::getSingleton().getCamera())
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
	lerpPlayerPos(dt);
	m_camera->setPosition( Ogre::Math::lerp<Ogre::Vector3>(m_camera->getPosition(),
		LaneSettings::getSingleton().getVectorOf(1,m_player->getPolarCoordinates().theta,m_height)*m_distance, MainUpdate::getSingleton().getDeltaTime()* 2.0)  );
	m_camera->lookAt(m_lerpedPlayerPos+Vector3(0.0,400.0,0.0));
}

void PlayerCameraStateNormal::lerpPlayerPos(const Ogre::Real& dt)
{
	m_lerpedPlayerPos = Math::lerp(m_lerpedPlayerPos, m_player->getNode()->getPosition(), dt*8.0);
}