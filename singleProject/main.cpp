// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LevelManager.h"
#include "LevelOne.h"
#include "MainUpdate.h"
#include "OgreCore.h"
#include "OISCore.h"
#include "LaneSettings.h"
#include "TBCRay.h"

int main()
{
	try
	{
		unique_ptr<OgreCore> ogreCore(new OgreCore());
		OgreCore::getSingletonPtr()->initRoot();
		OgreCore::getSingletonPtr()->initWindow(1024,576,"TBC");
		OgreCore::getSingletonPtr()->initSceneManager();
		OgreCore::getSingletonPtr()->initCamera("MainCamera");
		OgreCore::getSingletonPtr()->initViewport();
		OgreCore::getSingletonPtr()->initOverlaySystem();
		OgreCore::getSingletonPtr()->initScript();
		OgreCore::getSingletonPtr()->initResources();
		OgreCore::getSingletonPtr()->getSceneMgr()->showBoundingBoxes(true);

		unique_ptr<OISCore> oisCore(new OISCore());
		oisCore->init();

		unique_ptr<LaneSettings> laneSettings = unique_ptr<LaneSettings>(new LaneSettings() );
		laneSettings->initLanes();
		unique_ptr<TBCRay> raycasting = unique_ptr<TBCRay>(new TBCRay(OgreCore::getSingletonPtr()->getSceneMgr()));

		LevelManager levelMgr(new LevelOne());
		unique_ptr<MainUpdate> mainUpdate(new MainUpdate(&levelMgr));
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