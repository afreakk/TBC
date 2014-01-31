#include "stdafx.h"
#include "PlayerCameraStateLERP.h"
#include "../OgreCore/OgreCore.h"
#include "../GameLevels/MainUpdate.h"
PlayerCameraStateLERP::PlayerCameraStateLERP(SceneNode* playerNode) 
: m_playerNode(playerNode)
, m_camera(OgreCore::getSingleton().getCamera())
, m_lerp(0.0)
, m_r(0.0)
{
}


PlayerCameraStateLERP::~PlayerCameraStateLERP()
{
}

void PlayerCameraStateLERP::update()
{
	if (m_lerp < 1.0)
		m_lerp += MainUpdate::getSingleton().getDeltaTime()/1.5;
	m_r += MainUpdate::getSingleton().getDeltaTime()/3.5;
	m_camera->setPosition( Ogre::Math::lerp(m_camera->getPosition(), m_playerNode->getPosition()+Vector3(sin(m_r),0.3,cos(m_r)),m_lerp ));
	m_camera->lookAt(m_playerNode->getPosition());
}
