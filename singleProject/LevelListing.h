#pragma once
enum class LevelID
{
    NONE,
    LEVEL_INTRO,
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_MENU
};
inline std::ostream& operator<<(std::ostream& out, const LevelID value){
	static std::map<LevelID, std::string> strings;
	if (strings.size() == 0){
#define INSERT_ELEMENT(p) strings[p] = #p
		INSERT_ELEMENT(LevelID::LEVEL_ONE);
		INSERT_ELEMENT(LevelID::LEVEL_TWO);
		INSERT_ELEMENT(LevelID::LEVEL_MENU);
#undef INSERT_ELEMENT
	}

	return out << strings[value];
}

