#include "stdafx.h"
#include "PlayerCameraStateNormal.h"
#include "../OgreCore/OgreCore.h"
PlayerCameraStateNormal::PlayerCameraStateNormal(SceneNode* playerNode) 
: m_playerNode(playerNode)
, m_camera(OgreCore::getSingleton().getCamera())
, m_distance(1.35)
{
}


PlayerCameraStateNormal::~PlayerCameraStateNormal()
{
}

void PlayerCameraStateNormal::update()
{
	m_camera->setPosition(m_playerNode->getPosition()*m_distance+Vector3(0.0, 0.5, 0.0));
	m_camera->lookAt(Vector3::ZERO);
}
