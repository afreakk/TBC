#pragma once
#include "SaveGameIO.h"
#include "MainLevelSetter.h"
class GameStarter
{
public:
	static void startNewGame();
	static bool resumeGame();
	static bool resume;
	static Ogre::Real resumePos;
	static TutorialScript savedTutPoint;
	static unsigned mutantsAlreadyKilled;
	static unsigned mutantsAlreadyAlive;
private:
	static SaveGameIO m_savedData;
	static MainLevelEnums translateEnum(LevelID id);
};

