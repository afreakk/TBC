#include "stdafx.h"
#include "PlayerCameraStateLERP.h"
#include "../OgreCore/OgreCore.h"

PlayerCameraStateLERP::PlayerCameraStateLERP() :m_playerNode(nullptr), m_camera(nullptr)
{
}


PlayerCameraStateLERP::~PlayerCameraStateLERP()
{
}

void PlayerCameraStateLERP::update()
{
	m_camera->lookAt(m_playerNode->getPosition());
}
void PlayerCameraStateLERP::init(SceneNode* playerNode)
{
	m_playerNode = playerNode;
	m_camera = OgreCore::getSingletonPtr()->getCamera();
}
void PlayerCameraStateLERP::exit()
{

}