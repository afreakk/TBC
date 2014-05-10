#include "ILevel.h"
class LevelIntro : public ILevel
{
public:
	LevelIntro();
	~LevelIntro();
	bool update() override;
private:
	Ogre::Real m_timeElapsed;
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::Rectangle* m_rBackground;
	std::vector<std::string> m_sheetNames;
	std::vector<std::string>::iterator m_currentSprite;
	std::vector<Ogre::Real> m_frameTimings;
	std::vector<Ogre::Real>::iterator m_currentTime;

	void initSheetNames();
	void initTimings();
	void setNewFrame(bool increment=true);
	void incrementCurrentTime();
};