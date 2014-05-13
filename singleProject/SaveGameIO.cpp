#include "stdafx.h"
//------------||||||||||||||333333333333333333333333333333>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "SaveGameIO.h"
#include "MainUpdate.h"
#include "Player.h"
#include "PlayerContainer.h"
SaveGameIO::SaveGameIO()
{

}
void SaveGameIO::saveToFile(const std::string& filename)
{
	auto levelID = MainUpdate::getSingleton().getLevelID();
	std::string levelIDString;
	std::string thetaString = boost::lexical_cast<std::string, Ogre::Real>( PlayerContainer::getSingleton().getPlayer()->getPolarCoordinates().theta );
	switch (levelID)
	{
	case LevelID::LEVEL_INTRO:
		assert(0);
		break;
	case LevelID::LEVEL_ONE:
		levelIDString = "LEVEL_ONE";
		break;
	case LevelID::LEVEL_TWO:
		levelIDString = "LEVEL_TWO";
		break;
	case LevelID::LEVEL_MENU:
		assert(0);
		break;
	default:
		assert(0);
		break;
	}
	ofstream saveFile;
	saveFile.open(filename);
	saveFile << levelIDString << endl;
	saveFile << thetaString << endl;
	saveFile.close();
}
std::pair<LevelID, Ogre::Real> SaveGameIO::loadFromFile(const std::string& filename)
{
	std::pair<LevelID, Ogre::Real> data;
	std::vector<std::string> loadedStrings;
	if (!stringsFromFile(loadedStrings, filename, 2))
		return std::pair<LevelID, Ogre::Real>(LevelID::NONE, 0.0f);
	cout << "past no return" << endl;
	data.first = levelIDFromString(loadedStrings[0]);
	data.second = boost::lexical_cast<Ogre::Real, std::string>(loadedStrings[1]);
	return data;
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