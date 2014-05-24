#include "stdafx.h"
#include "MainLevelSetter.h"
#include "MainUpdate.h"
#include "OgreCore.h"
#include "OISCore.h"
#include "LaneSettings.h"
#include "TBCRay.h"
#include "GUIResources.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"
#include "PlayerGlobalStats.h"
#include "CoreCompositor.h"
#include "SoundFactory.h"
#include "LoadingScreen.h"
#include "GameConsole.h"
int main()
{
	try
	{
		LoadingBar loadingBar;
		unique_ptr<SoundFactory> soundFactory(new SoundFactory());
		unique_ptr<OgreCore> ogreCore(new OgreCore());
		OgreCore::getSingletonPtr()->initRoot();
		OgreCore::getSingletonPtr()->initWindow(1280,720,"TBC");
		OgreCore::getSingletonPtr()->initSceneManager();
		OgreCore::getSingletonPtr()->initCamera("MainCamera");
		OgreCore::getSingletonPtr()->initViewport();
		OgreCore::getSingletonPtr()->initOverlaySystem();
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/gui/misc/loadingBG" , "FileSystem", "BootstrapA"); // 4 loadingbar
		try
		{
            Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("BootstrapA");
		}
		catch (Ogre::Exception e)
		{
			cout << e.what() << endl;
		}
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/OgreCore.zip", "Zip", "Bootstrap"); // 4 loadingbar
		unique_ptr<RootOverlay> rootOverlay = unique_ptr<RootOverlay>(new RootOverlay("GameOverlay"));
		rootOverlay->show(true);
		loadingBar.start(OgreCore::getSingleton().getWindow(), 8, 0,1.0f);
		OgreCore::getSingletonPtr()->initScript();
		OgreCore::getSingletonPtr()->initResources();
		OgreCore::getSingleton().initShadowCasting();
//		OgreCore::getSingletonPtr()->getSceneMgr()->showBoundingBoxes(true);
		unique_ptr<Gorilla::Silverback> gorilla_silverback = unique_ptr<Gorilla::Silverback>(new Gorilla::Silverback());
		gorilla_silverback->loadAtlas("dejavu");

		unique_ptr<OISCore> oisCore(new OISCore());
		oisCore->init();

		unique_ptr<GameConsole> gameConsole(new GameConsole());

		unique_ptr<LaneSettings> laneSettings = unique_ptr<LaneSettings>(new LaneSettings() );
		laneSettings->initLanes();
		unique_ptr<TBCRay> raycasting = unique_ptr<TBCRay>(new TBCRay(OgreCore::getSingletonPtr()->getSceneMgr()));
    
		unique_ptr<GlobalVariables> m_globalVars = unique_ptr<GlobalVariables>(new GlobalVariables());
		unique_ptr<PlayerGlobalStats> m_playerStats = unique_ptr<PlayerGlobalStats>(new PlayerGlobalStats());
		unique_ptr<MutantGlobalStats> m_mutantGlobalStats = unique_ptr<MutantGlobalStats>(new MutantGlobalStats());

		unique_ptr<MainLevelSetter> lvlSetter = unique_ptr<MainLevelSetter>(new MainLevelSetter(MainLevelEnums::MENU));
		unique_ptr<MainUpdate> mainUpdate(new MainUpdate(lvlSetter->getLevelManager()));
        new CoreCompositor(OgreCore::getSingleton().getCamera()->getViewport());
		loadingBar.finish();
		Ogre::Root::getSingletonPtr()->startRendering();
		cout << "rendering stopped ." << endl;
	}
	catch (Ogre::Exception &e)
	{
		std::cout << "!!!!Ogre::Exception!!!!\n" << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "!!!!std::exception!!!!\n" << e.what() << std::endl;;
	}
	std::cout << std::endl << "Exiting main." << std::endl;
	char p;
	std::cin >> p;
	return 0;
}