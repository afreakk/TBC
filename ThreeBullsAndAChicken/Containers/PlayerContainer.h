#pragma once
#include "../BehaviourObject/Player.h"
#include "../BehaviourObjectHandler/PlayerHandler.h"
class PlayerContainer : public Singleton<PlayerContainer>
{
public:
	PlayerContainer()
	: m_player(new Player())
	, m_handler(new PlayerHandler(m_player.get()))
	{

	}
	~PlayerContainer()
	{

	}
	void update()
	{
		m_player->update();
		m_handler->update();
	}
	Player* getPlayer()
	{
		return m_player.get();
	}
private:
	unique_ptr<Player> m_player;
	unique_ptr<PlayerHandler> m_handler;

};

template<> PlayerContainer* Ogre::Singleton<PlayerContainer>::msSingleton = 0;