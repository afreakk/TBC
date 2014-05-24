#include "stdafx.h"
#include "DeathScreen.h"
#include "MainLevelSetter.h"
#include "PlayerContainer.h"

DeathScreen::DeathScreen()
: m_deathMenu(nullptr)
{
}


DeathScreen::~DeathScreen()
{
}
#include "OgreCore.h"
#include "PlayerContainer.h"
#include "Player.h"
#include "ModelHandler.h"
void DeathScreen::updateDeathMenu()
{
	if (m_deathMenu)
	{
		auto keyClicked = m_deathMenu->getButtonClicked();
		if (keyClicked != ButtonType::none)
		{
            auto smgr = OgreCore::getSingleton().getSceneMgr();
            smgr->clearSpecialCaseRenderQueues();
            smgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_EXCLUDE);
            PlayerContainer::getSingleton().getPlayer()->getModelHandler().getEntity()->setRenderQueueGroup(m_playerRenderQueueGroup);
			switch (keyClicked)
			{
			case ButtonType::gotoMainMenu:
				m_saveGame.saveToFile();
				MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::MENU);
				break;
			case ButtonType::retry:
                PlayerContainer::getSingleton().respawnPlayer();
				m_deathMenu.reset();
				break;
			case ButtonType::backToMenu:
                //---------------------|||||||||========
                // escape == backToMenu , this is Filler
				break;
			default:
				assert(0);
				break;
                //---------------------|||||||||========
			}
		}
	}
	else if (PlayerContainer::getSingleton().isPlayerDead())
	{
		m_playerRenderQueueGroup = PlayerContainer::getSingleton().getPlayer()->getModelHandler().getEntity()->getRenderQueueGroup();
		PlayerContainer::getSingleton().getPlayer()->getModelHandler().getEntity()->setRenderQueueGroup(RENDER_QUEUE_OVERLAY);
        auto smgr = OgreCore::getSingleton().getSceneMgr();
        smgr->clearSpecialCaseRenderQueues();
        smgr->addSpecialCaseRenderQueue(RENDER_QUEUE_OVERLAY);
        smgr->addSpecialCaseRenderQueue(RENDER_QUEUE_9);
        smgr->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_INCLUDE);

		m_deathMenu.reset();
		m_deathMenu = unique_ptr<DeathMenu>(new DeathMenu());
	}
}