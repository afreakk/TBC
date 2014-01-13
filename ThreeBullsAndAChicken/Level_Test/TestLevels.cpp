#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Levels/LevelOne.h"
#include "../Levels/LevelMenu.h"
#include "../Levels/LevelManager.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLevels
{		

	TEST_CLASS(TEST_LevelID)
	{
	public:
		
		LevelOne levelOne;
		LevelMenu levelMenu;
		TEST_LevelID()
		{
		}
		TEST_CLASS_INITIALIZE(LevelOneInitialize)
		{
		}
		TEST_METHOD(Test_levelID)
		{
		}
		TEST_METHOD(Test_Levels_levelID)
		{
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_ONE), static_cast<int>(levelOne.getID()));
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_MENU), static_cast<int>(levelMenu.getID()));
			for (int i = 0; i < 100; i++)
			{
				levelOne.update();
				levelMenu.update();
			}
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_ONE), static_cast<int>(levelOne.getID()));
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_MENU), static_cast<int>(levelMenu.getID()));
		}

	};
	TEST_CLASS(TEST_LevelManager)
	{
	public:
		LevelManager* levelManager;

		TEST_LevelManager()
		{
		}
		TEST_METHOD(TEST_LevelManager_InitializeLVL)
		{
			levelManager = new LevelManager(new LevelOne());
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_ONE), static_cast<int>( levelManager->getCurrentLevelID() ) );
			delete levelManager;
		}
		TEST_METHOD(TEST_LevelManager_changeLevel)
		{
			levelManager = new LevelManager(new LevelOne());
			for (int i = 0; i < 50; i++)
				levelManager->update();
			levelManager->changeLevel(new LevelMenu());
			for (int i = 0; i < 50; i++)
				levelManager->update();
			Assert::AreEqual(static_cast<int>(LevelID::LEVEL_MENU), static_cast<int>( levelManager->getCurrentLevelID() ) );
			delete levelManager;
		}


	};
}