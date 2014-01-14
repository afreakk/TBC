// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Levels/LevelManager.h"
#include "../GameLevels/LevelOne.h"
#include "../GameLevels/MainUpdate.h"
#include "../OgreCore/OgreCore.h"
#include "../OgreCore/OISCore.h"
#include <exception>

void PrintFullPath(char * partialPath)
{
	char full[_MAX_PATH];
	if (_fullpath(full, partialPath, _MAX_PATH) != NULL)
		printf("Full path is: %s\n", full);
	else
		printf("Invalid path\n");
}
int main()
{
	try
	{
		new OgreCore();
		OgreCore::getSingletonPtr()->initRoot();
		OgreCore::getSingletonPtr()->initResources();
		OgreCore::getSingletonPtr()->initWindow(800,600,"TBC");
		OgreCore::getSingletonPtr()->initSceneManager();
		OgreCore::getSingletonPtr()->initCamera("MainCamera");
		OgreCore::getSingletonPtr()->initViewport();

		new OISCore();
		OISCore::getSingletonPtr()->init();

		LevelManager levelMgr(new LevelOne());
		new MainUpdate(&levelMgr);
		Ogre::Root::getSingletonPtr()->startRendering();
		delete MainUpdate::getSingletonPtr();
		delete Ogre::Root::getSingletonPtr();
	}
	catch (Ogre::Exception &e)
	{
		std::cout << "!!!!Ogre::Exception!!!!\n" << e.what() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "!!!!std::exception!!!!\n" << e.what() << std::endl;;
	}
	PrintFullPath(".\\");
	std::cout << std::endl << "Exiting main." << std::endl;
	char p;
	std::cin >> p;
	return 0;
}