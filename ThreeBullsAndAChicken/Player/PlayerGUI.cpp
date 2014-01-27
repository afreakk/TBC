#include "stdafx.h"
#include "PlayerGUI.h"
#include "../OgreCore/OgreCore.h"
template<> PlayerGUI* Ogre::Singleton<PlayerGUI>::msSingleton = 0;
PlayerGUI::PlayerGUI()
{
}

PlayerGUI::~PlayerGUI()
{
}


void PlayerGUI::energyRefresh(unsigned newEnergy)
{
	m_guiStyle.setEnergy(newEnergy);
}