#pragma once
#include "OgreSingleton.h"
#include <memory>
class PlayerHandler;
class Player;
class PlayerContainer : public Ogre::Singleton<PlayerContainer>
{
public:
	PlayerContainer();
	~PlayerContainer();
	void update();
	Player* getPlayer();
	PlayerHandler* getHandler();
	void killPlayer();
private:
	std::unique_ptr<Player> m_player;
	std::unique_ptr<PlayerHandler> m_handler;

};
