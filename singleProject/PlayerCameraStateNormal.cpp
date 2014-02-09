#include "stdafx.h"
#include "PlayerCameraStateNormal.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "PlayerCameraVars.h"
PlayerCameraStateNormal::PlayerCameraStateNormal(SceneNode* playerNode) 
: m_playerNode(playerNode)
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
	if (m_lerp< 1.0)
		m_lerp += MainUpdate::getSingleton().getDeltaTime();
	m_camera->setPosition( Ogre::Math::lerp(m_camera->getPosition(),m_playerNode->getPosition()*m_distance+Vector3(0.0, m_height, 0.0), m_lerp)  );
	m_camera->lookAt(Vector3::ZERO);
}
