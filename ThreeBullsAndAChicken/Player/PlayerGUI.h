#pragma once
#include "stdafx.h"
#include "EnergySubscriber.h"
#include "../Other/MovableText.h"
#include "../PlayerGUI/PlayerGUIStyle.h"
class PlayerGUI : public Ogre::Singleton<PlayerGUI>, public EnergySubscriber
{
public:
	PlayerGUI();
	~PlayerGUI();
	void energyRefresh(unsigned) override;
	void init();
private:
	PlayerGUIStyle m_guiStyle;
};

