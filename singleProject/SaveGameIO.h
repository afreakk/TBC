#pragma once
#include "LevelListing.h"

class SaveGameIO
{
public:
	SaveGameIO();
	void saveToFile(const std::string& filename="wutup");
	std::pair<LevelID,Ogre::Real> loadFromFile(const std::string& filename="wutup");
private:
	bool stringsFromFile(std::vector<std::string>& arr ,const std::string& filename, unsigned lineCount);

	LevelID levelIDFromString(const std::string& text);
};