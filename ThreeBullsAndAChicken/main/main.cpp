// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Levels/LevelManager.h"
#include "../GameLevels/LevelOne.h"
#include "../GameLevels/MainUpdate.h"
#include "../OgreCore/OgreCore.h"
#include "../OgreCore/OISCore.h"
#include "../Shaders/MutantShader.h"

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
		OgreCore::getSingletonPtr()->initWindow(1024,576,"TBC");
		OgreCore::getSingletonPtr()->initSceneManager();
		OgreCore::getSingletonPtr()->initCamera("MainCamera");
		OgreCore::getSingletonPtr()->initViewport();
		OgreCore::getSingletonPtr()->initOverlaySystem();
		OgreCore::getSingletonPtr()->initResources();

		new OISCore();
		OISCore::getSingletonPtr()->init();

		MutantShader mutantShader;

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