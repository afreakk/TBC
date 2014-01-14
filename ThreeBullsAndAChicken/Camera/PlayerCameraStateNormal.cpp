#include "stdafx.h"
#include "PlayerCameraStateNormal.h"

PlayerCameraStateNormal::PlayerCameraStateNormal() :m_camera(nullptr), m_distance(2.0)
{
}


PlayerCameraStateNormal::~PlayerCameraStateNormal()
{
}

void PlayerCameraStateNormal::update()
{
	m_camera->setPosition(m_playerNode->getPosition()*m_distance);
	m_camera->lookAt(Ogre::Vector3::ZERO);
}
#include "../OgreCore/OgreCore.h"
void PlayerCameraStateNormal::init(Ogre::SceneNode* playerNode)
{
	m_playerNode = playerNode;
	m_camera = OgreCore::getSingletonPtr()->getCamera();
}
void PlayerCameraStateNormal::exit()
{

}