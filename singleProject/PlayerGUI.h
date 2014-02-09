#pragma once
#include "MessageSubscriber.h"
#include "MovableText.h"
#include "PlayerGUIStyle.h"
class PlayerGUI : public Ogre::Singleton<PlayerGUI>, public MessageSubscriber<unsigned>
{
public:
	PlayerGUI();
	~PlayerGUI();
	void notify(unsigned) override;
private:
	PlayerGUIStyle m_guiStyle;
};

