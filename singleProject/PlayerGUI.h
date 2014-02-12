#pragma once
#include "MessageSubscriber.h"
#include "MovableText.h"
#include "BarTypes.h"
#include "PlayerStatus.h"
class PlayerGUI : public Ogre::Singleton<PlayerGUI>, public MessageSubscriber<PlayerStatus>
{
public:
	PlayerGUI();
	~PlayerGUI();
	void notify(PlayerStatus) override;
private:
	EnergyBar m_energyBar;
	HealthBar m_healthBar;
};

