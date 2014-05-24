#include "stdafx.h"
#include "PlayerCameraState.h"
#include "LaneSettings.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "MainUpdate.h"
#include "OgreCore.h"

Ogre::Vector3 PlayerCameraState::m_lerpedPlayerPos = Vector3::ZERO;
Ogre::Real PlayerCameraState::m_playerThetaLerp = 0.0f;
PlayerCameraState::PlayerCameraState()
: m_camera(OgreCore::getSingleton().getCamera())
{

}
void PlayerCameraState::setCameraPos(const Ogre::Real& height, const Ogre::Real& distance)
{
	Ogre::Vector3 destination = LaneSettings::getSingleton().getVectorOf(1, getTiltedPlayerPos(), height)*distance;
	Ogre::Real weight = MainUpdate::getSingleton().getScaledDeltaTime()* 2.0;
    m_camera->setPosition( Ogre::Math::lerp<Ogre::Vector3>(m_camera->getPosition(),destination, weight)  );
}
const Ogre::Vector3& PlayerCameraState::getTiltedLerpedPlayerPos(const Ogre::Real& dt)
{
	m_playerThetaLerp = Math::lerp(m_playerThetaLerp, getTiltedPlayerPos(), dt*8.0);
	m_lerpedPlayerPos = LaneSettings::getSingleton().getVectorOf(1, m_playerThetaLerp, 150.0f);
	//m_lerpedPlayerPos = Math::lerp(m_lerpedPlayerPos, Vector3(m_player->getNode()->getPosition()., dt*8.0);
	return m_lerpedPlayerPos;
}
Ogre::Real PlayerCameraState::getTiltedPlayerPos()
{
	return PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta + S_CAMERA_RIGHT_TILT;
}