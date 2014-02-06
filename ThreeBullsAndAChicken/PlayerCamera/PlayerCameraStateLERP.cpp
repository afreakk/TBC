#include "stdafx.h"
#include "PlayerCameraStateLERP.h"
#include "../OgreCore/OgreCore.h"
#include "../GameLevels/MainUpdate.h"
#include "../Camera/PlayerCameraVars.h"
PlayerCameraStateLERP::PlayerCameraStateLERP(SceneNode* playerNode) 
: m_playerNode(playerNode)
, m_camera(OgreCore::getSingleton().getCamera())
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

void PlayerCameraStateLERP::update()
{
	if (m_lerp < 1.0)
		m_lerp += MainUpdate::getSingleton().getDeltaTime();
	m_r += MainUpdate::getSingleton().getDeltaTime()*m_spinSpeed;
	m_camera->setPosition( Ogre::Math::lerp(m_camera->getPosition(), m_playerNode->getPosition()+Vector3(sin(m_r)*m_distance,m_height,cos(m_r)*m_distance),m_lerp ));
	m_camera->lookAt(m_playerNode->getPosition());
}
