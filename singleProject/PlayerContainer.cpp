#include "stdafx.h"
#include "PlayerContainer.h"

#include "ConfigScriptLoader.h"
#include "Player.h"
#include "PlayerHandler.h"
#include "UnitCircleMovement.h"
#include "PlayerGlobalStats.h"
#include "GameStarter.h"
using namespace Ogre;
template<> PlayerContainer* Ogre::Singleton<PlayerContainer>::msSingleton = 0;
PlayerContainer::PlayerContainer()
: m_player(nullptr)
, m_handler(nullptr)
{
    ConfigNode* rootNode = ConfigScriptLoader::getSingleton().getConfigScript("entity", "Player");
    unsigned lane = rootNode->findChild("lane")->getValueU(0);
	Real r;
	if (GameStarter::resume)
		r = GameStarter::resumePos;
	else
        r = rootNode->findChild("r")->getValueR(0);
    m_player = unique_ptr<Player>(new Player(polarFromStarting(r, lane)));
    m_handler = unique_ptr<PlayerHandler>(new PlayerHandler(m_player.get()));
}


PlayerContainer::~PlayerContainer()
{
	m_player.reset();
}

void PlayerContainer::destroyHandlers()
{
	m_handler.reset();
}
void PlayerContainer::update()
{
    m_player->update();
    m_handler->update();
}
Player* PlayerContainer::getPlayer()
{
    return m_player.get();
}
PlayerHandler* PlayerContainer::getHandler()
{
    return m_handler.get();
}
void PlayerContainer::killPlayer()
{
    m_handler->switchState(PLAYER_HANDLER_STATE::DEAD);
}
void PlayerContainer::notify(PlayerStatus p)
{
	if (p.health == 0)
		killPlayer();
}
void PlayerContainer::respawnPlayer()
{
	PlayerGlobalStats::getSingleton().setHealth(100);
	m_handler->switchState(PLAYER_HANDLER_STATE::NORMAL);
}