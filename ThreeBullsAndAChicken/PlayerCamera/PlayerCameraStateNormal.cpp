#include "stdafx.h"
#include "PlayerCameraStateNormal.h"

PlayerCameraStateNormal::PlayerCameraStateNormal() :m_camera(nullptr), m_distance(1.4)
{
}


PlayerCameraStateNormal::~PlayerCameraStateNormal()
{
}

void PlayerCameraStateNormal::update()
{
	m_camera->setPosition(m_playerNode->getPosition()*m_distance+Vector3(0.0, 0.3, 0.0));
	m_camera->lookAt(Vector3::ZERO);
}
#include "../OgreCore/OgreCore.h"
void PlayerCameraStateNormal::init(SceneNode* playerNode)
{
	m_playerNode = playerNode;
	m_camera = OgreCore::getSingletonPtr()->getCamera();
}
void PlayerCameraStateNormal::exit()
{

}