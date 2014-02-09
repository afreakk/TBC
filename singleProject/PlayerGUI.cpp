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


void PlayerGUI::notify(unsigned newEnergy)
{
	m_guiStyle.setEnergy(newEnergy);
}