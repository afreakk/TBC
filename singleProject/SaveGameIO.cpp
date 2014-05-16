#include "stdafx.h"
#include "SaveGameIO.h"
#include "MainUpdate.h"
#include "Player.h"
#include "PlayerContainer.h"
#include "MutantContainer.h"
/*
FileSpec:
-levelID
-theta
-mutantsKilled
-mutantsAlive
-tutorialIdx
*/
SaveGameIO::SaveGameIO()
{

}
void SaveGameIO::saveToFile(const std::string& filename)
{
	std::string levelIDString = levelIDToString(MainUpdate::getSingleton().getLevelID());
	std::string thetaString = boost::lexical_cast<std::string, Ogre::Real>( PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta );
	ofstream saveFile;
	saveFile.open(filename);
	saveFile << levelIDString << endl;
	saveFile << thetaString << endl;
	saveFile << MutantContainer::getSingleton().getMutantsKilled() << endl;
	saveFile << MutantContainer::getSingleton().getMutantIt().size() << endl;
	writeTutorialData(saveFile, MainUpdate::getSingleton().getLevelID());
	saveFile.close();
}
SaveGameData SaveGameIO::loadFromFile(const std::string& filename)
{
	SaveGameData data;
	std::vector<std::string> loadedStrings;
	if (!stringsFromFile(loadedStrings, filename, 5))
	{
		data.error = true;
		return data;
	}
	cout << "past no return" << endl;
	data.levelID = levelIDFromString(loadedStrings[0]);
	data.theta = boost::lexical_cast<Ogre::Real, std::string>(loadedStrings[1]);
	data.mutantsKilled = boost::lexical_cast<unsigned, std::string> (loadedStrings[2]);
	data.mutantsAlive = boost::lexical_cast<unsigned, std::string> (loadedStrings[3]);
	data.tutorialPos = static_cast<TutorialScript>(boost::lexical_cast<int, std::string>(loadedStrings[4]));
	return data;
}
std::string SaveGameIO::levelIDToString(LevelID levelID)
{
	switch (levelID)
	{
	case LevelID::LEVEL_INTRO:
		assert(0);
		break;
	case LevelID::LEVEL_ONE:
		return "LEVEL_ONE";
		break;
	case LevelID::LEVEL_TWO:
		return "LEVEL_TWO";
		break;
	case LevelID::LEVEL_MENU:
		assert(0);
		break;
	default:
		assert(0);
		break;
	}
	return "fatal_error:)";
}
#include "Tutorial.h"
void SaveGameIO::writeTutorialData(ofstream& saveFile, LevelID levelID)
{
	if (levelID == LevelID::LEVEL_ONE)
        saveFile << static_cast<int>(Tutorial::getTooltipIdx()) << endl;
	else
		saveFile << 0 << endl;
}
bool SaveGameIO::stringsFromFile(std::vector<std::string>& arr ,const std::string& filename, unsigned lineCount)
{
	cout << "opening file <<" << filename << endl;
	ifstream myfile(filename);
	arr.resize(lineCount);
	if (myfile.is_open())
	{
		for (size_t i = 0; i < lineCount; i++)
		{
			if (!getline(myfile, arr[i]))
			{
				cout << "too many lines or something" << endl;
				return false;
			}
			cout << arr[i] << endl;
		}
		myfile.close();
	}
	else
	{
		throw std::exception("my file not goood..");
		return false;
	}
	return true;
}
LevelID SaveGameIO::levelIDFromString(const std::string& text)
{
	if (text == "LEVEL_ONE")
		return LevelID::LEVEL_ONE;
	else if (text == "LEVEL_TWO")
		return LevelID::LEVEL_TWO;
	assert(0);
	return LevelID::LEVEL_INTRO;
}