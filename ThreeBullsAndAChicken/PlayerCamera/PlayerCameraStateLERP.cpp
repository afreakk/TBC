#include "stdafx.h"
#include "PlayerCameraStateLERP.h"
#include "../OgreCore/OgreCore.h"

PlayerCameraStateLERP::PlayerCameraStateLERP(SceneNode* playerNode) :m_playerNode(playerNode), m_camera(OgreCore::getSingleton().getCamera())
{
}


PlayerCameraStateLERP::~PlayerCameraStateLERP()
{
}

void PlayerCameraStateLERP::update()
{
	m_camera->setPosition(m_playerNode->getPosition()*1.2+Vector3(0.0,0.2,0.0));
	m_camera->lookAt(m_playerNode->getPosition());
}
