#include "stdafx.h"
#include "LevelIntro.h"
#include "OgreCore.h"
#include "MainUpdate.h"
#include "SoundFactory.h"
LevelIntro::LevelIntro()
: ILevel(LevelID::LEVEL_INTRO)
, m_timeElapsed(0.0f)
{
	initSheetNames();
	initTimings();
	Gorilla::Silverback::getSingleton().loadAtlas("introSheet");
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "introSheet");
	m_layer = m_screen->createLayer(0);
	Ogre::Real vpW = m_screen->getWidth(); 
	Ogre::Real vpH = m_screen->getHeight();
	m_rBackground = m_layer->createRectangle(0, 0, vpW, vpH);
    //--
	m_currentTime = m_frameTimings.begin();
	m_currentSprite = m_sheetNames.begin();
	setNewFrame(false);
    //--
	SoundFactory::getSingleton().playMusic("music/intro.ogg");
}
LevelIntro::~LevelIntro()
{
	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
}
void LevelIntro::setNewFrame(bool increment)
{
	if (increment)
		m_currentSprite++;
	m_rBackground->background_image(*m_currentSprite);
}
#include "MainLevelSetter.h"
bool LevelIntro::update()
{
	m_timeElapsed += MainUpdate::getSingleton().getDeltaTime();
	if (m_currentTime != m_frameTimings.end())
	{
        if (m_timeElapsed > *m_currentTime)
        {
            setNewFrame();
            m_currentTime++;
        }
	}
	else
        MainLevelSetter::getSingleton().changeLevel(MainLevelEnums::LVL1);
	return true;
}
void LevelIntro::initSheetNames()
{
	m_sheetNames.push_back("intro_one");
	m_sheetNames.push_back("intro_two");
	m_sheetNames.push_back("one");
	m_sheetNames.push_back("two");
	m_sheetNames.push_back("three");
	m_sheetNames.push_back("four");
	m_sheetNames.push_back("five");
	m_sheetNames.push_back("six");
	m_sheetNames.push_back("seven");
	m_sheetNames.push_back("eight");
	m_sheetNames.push_back("nine");
	m_sheetNames.push_back("ten");
	m_sheetNames.push_back("eleven");
	m_sheetNames.push_back("twelve");
	m_sheetNames.push_back("thirteen");
	m_sheetNames.push_back("fourteen");
}
void LevelIntro::initTimings()
{
	m_frameTimings.push_back(4.3);
	m_frameTimings.push_back(9.6);
	m_frameTimings.push_back(15.04);
	m_frameTimings.push_back(37.08);
	m_frameTimings.push_back(44.08);
	m_frameTimings.push_back(51.18);
	m_frameTimings.push_back(63.17);
	m_frameTimings.push_back(70.29);
	m_frameTimings.push_back(76.01);

	m_frameTimings.push_back(83.00);
	m_frameTimings.push_back(92.09);
	m_frameTimings.push_back(104.04);
	m_frameTimings.push_back(116.04); // fadeout
	m_frameTimings.push_back(128.07); // logo FadeIn
	m_frameTimings.push_back(140.03); // logo fade2White
}