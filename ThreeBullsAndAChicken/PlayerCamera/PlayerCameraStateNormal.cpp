#include "stdafx.h"
#include "PlayerCameraStateNormal.h"
#include "../OgreCore/OgreCore.h"
#include "../GameLevels/MainUpdate.h"
PlayerCameraStateNormal::PlayerCameraStateNormal(SceneNode* playerNode) 
: m_playerNode(playerNode)
, m_camera(OgreCore::getSingleton().getCamera())
, m_distance(1.30)
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
	m_camera->setPosition( Ogre::Math::lerp(m_camera->getPosition(),m_playerNode->getPosition()*m_distance+Vector3(0.0, 0.4, 0.0), m_lerp)  );
	m_camera->lookAt(Vector3::ZERO);
}
