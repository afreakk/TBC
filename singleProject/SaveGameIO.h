#pragma once
#include "LevelListing.h"
#include "TutorialEnums.h"
struct SaveGameData
{
	bool error;
	LevelID levelID;
	Ogre::Real theta;
	TutorialScript tutorialPos;
	unsigned mutantsKilled;
	unsigned mutantsAlive;
	unsigned energy;
	SaveGameData() : error(false), levelID(LevelID::NONE), theta(0.0f), tutorialPos(TutorialScript::none), mutantsKilled(0), mutantsAlive(0)
	{}
};
static const std::string savegameFile = "../media/saveGame/save_file.save";
class SaveGameIO
{
public:
	SaveGameIO();
	void saveToFile(const std::string& filename=savegameFile);
	SaveGameData loadFromFile(const std::string& filename=savegameFile);
private:
	bool stringsFromFile(std::vector<std::string>& arr ,const std::string& filename, unsigned lineCount);

	LevelID levelIDFromString(const std::string& text);
	void writeTutorialData(ofstream& saveFile, LevelID levelID);
	std::string levelIDToString(LevelID levelID);
};