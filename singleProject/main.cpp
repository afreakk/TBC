// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

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

int main()
{
	try
	{
		unique_ptr<OgreCore> ogreCore(new OgreCore());
		OgreCore::getSingletonPtr()->initRoot();
		OgreCore::getSingletonPtr()->initWindow(1280,720,"TBC");
		OgreCore::getSingletonPtr()->initSceneManager();
		OgreCore::getSingletonPtr()->initCamera("MainCamera");
		OgreCore::getSingletonPtr()->initViewport();
		OgreCore::getSingletonPtr()->initOverlaySystem();
		OgreCore::getSingletonPtr()->initScript();
		OgreCore::getSingletonPtr()->initResources();
		OgreCore::getSingleton().initShadowCasting();
//		OgreCore::getSingletonPtr()->getSceneMgr()->showBoundingBoxes(true);
		unique_ptr<GUIResources> guiResources = unique_ptr<GUIResources>(new GUIResources("GameOverlay"));
		guiResources->show(true);

		unique_ptr<OISCore> oisCore(new OISCore());
		oisCore->init();

		unique_ptr<LaneSettings> laneSettings = unique_ptr<LaneSettings>(new LaneSettings() );
		laneSettings->initLanes();
		unique_ptr<TBCRay> raycasting = unique_ptr<TBCRay>(new TBCRay(OgreCore::getSingletonPtr()->getSceneMgr()));

        new CoreCompositor(OgreCore::getSingleton().getCamera()->getViewport());
		unique_ptr<GlobalVariables> m_globalVars = unique_ptr<GlobalVariables>(new GlobalVariables());
		unique_ptr<PlayerGlobalStats> m_playerStats = unique_ptr<PlayerGlobalStats>(new PlayerGlobalStats());
        unique_ptr<MutantGlobalStats> m_mutantGlobalStats = unique_ptr<MutantGlobalStats>(new MutantGlobalStats());

		unique_ptr<MainLevelSetter> lvlSetter = unique_ptr<MainLevelSetter>(new MainLevelSetter(MainLevelEnums::LVL1));
		unique_ptr<MainUpdate> mainUpdate(new MainUpdate(lvlSetter->getLevelManager()));
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