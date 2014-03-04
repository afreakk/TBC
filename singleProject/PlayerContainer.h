#pragma once
#include "OgreSingleton.h"
#include <memory>
#include "PlayerStatus.h"
#include "MessageSubscriber.h"
class PlayerHandler;
class Player;
class PlayerContainer : public Ogre::Singleton<PlayerContainer>, public MessageSubscriber<PlayerStatus>
{
public:
	PlayerContainer();
	~PlayerContainer();
	void update();
	Player* getPlayer();
	PlayerHandler* getHandler();
	void notify(PlayerStatus) override;
	void destroyHandlers();
	void respawnPlayer();
private:
	void killPlayer();

	std::unique_ptr<Player> m_player;
	std::unique_ptr<PlayerHandler> m_handler;

};
