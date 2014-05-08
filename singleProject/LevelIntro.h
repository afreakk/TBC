#include "ILevel.h"
class LevelIntro : public ILevel
{
public:
	LevelIntro();
	~LevelIntro();
	bool update() override;
private:
	Gorilla::Screen* m_screen;
	Gorilla::Layer* m_layer;
	Gorilla::Rectangle* m_rBackground;
	std::vector<std::string> m_sheetNames;
	unsigned m_currentFrame;
	Ogre::Real m_timeElapsed;
	std::vector<Ogre::Real> m_frameTimings;
	std::vector<Ogre::Real>::iterator m_currentTime;

	void initSheetNames();
	void initTimings();
	void setNewFrame(bool increment=true);
	void incrementCurrentTime();
};