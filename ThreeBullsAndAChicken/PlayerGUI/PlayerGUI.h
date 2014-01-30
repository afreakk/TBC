#pragma once
#include "stdafx.h"
#include "../Templates/MessageSubscriber.h"
#include "../Other/MovableText.h"
#include "../PlayerGUI/PlayerGUIStyle.h"
class PlayerGUI : public Ogre::Singleton<PlayerGUI>, public MessageSubscriber<unsigned>
{
public:
	PlayerGUI();
	~PlayerGUI();
	void notify(unsigned) override;
private:
	PlayerGUIStyle m_guiStyle;
};

