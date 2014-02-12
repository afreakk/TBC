#include "stdafx.h"
#include "PlayerGUI.h"
#include "OgreCore.h"
template<> PlayerGUI* Ogre::Singleton<PlayerGUI>::msSingleton = 0;
PlayerGUI::PlayerGUI()
{
}

PlayerGUI::~PlayerGUI()
{
}


void PlayerGUI::notify(PlayerStatus playerStatus)
{
	m_energyBar.setValue(playerStatus.energy);
	m_healthBar.setValue(playerStatus.health);
}