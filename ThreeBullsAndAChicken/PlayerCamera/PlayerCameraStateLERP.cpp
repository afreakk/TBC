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
	m_camera->setPosition(m_playerNode->getPosition()*1.5+Vector3(0.0,1.0,0.0));
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