#include "stdafx.h"
#include "PlayerCameraVars.h"


template<> PlayerCameraVars* Ogre::Singleton<PlayerCameraVars>::msSingleton = 0;
PlayerCameraVars::PlayerCameraVars()
{
	parseScript();
}

void PlayerCameraVars::parseScript()
{
	ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "PlayerCameraNormal");
	m_playerCameraNormal.distance = rootNode->findChild("distance")->getValueR(0);
	m_playerCameraNormal.height = rootNode->findChild("height")->getValueR(0);

	rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "PlayerCameraLERP");
	m_playerCameraLerp.distance = rootNode->findChild("distance")->getValueR(0);
	m_playerCameraLerp.height = rootNode->findChild("height")->getValueR(0);
	m_playerCameraLerp.spinSpeed = rootNode->findChild("spinSpeed")->getValueR(0);
}

PlayerCameraVars::~PlayerCameraVars()
{
}
