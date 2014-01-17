#include "stdafx.h"
#include "PlayerGUI.h"
#include "PlayerStats.h"
#include "boost/lexical_cast.hpp"
#include "../OgreCore/OgreCore.h"
#include "Overlay/OgreOverlayManager.h"
template<> PlayerGUI* Ogre::Singleton<PlayerGUI>::msSingleton = 0;
PlayerGUI::PlayerGUI()
{
}

void PlayerGUI::init()
{
	PlayerStats::getSingletonPtr()->registerEnergySubscriber(this, "PlayerGUI");
}

PlayerGUI::~PlayerGUI()
{
	PlayerStats::getSingletonPtr()->removeEnergySubscriber("PlayerGUI");
}


void PlayerGUI::energyRefresh(unsigned newEnergy)
{
	m_guiStyle.setEnergy(newEnergy);
}