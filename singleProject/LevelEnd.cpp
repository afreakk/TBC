#include "stdafx.h"
#include "LevelEnd.h"
#include "OgreCore.h"
#include "SoundFactory.h"
LevelEnd::LevelEnd()
:ILevel(LevelID::LEVEL_END)
, m_time(0.0f)
{
	std::string gorillaFileName = "endSheet";
    Gorilla::Silverback::getSingleton().loadAtlas(gorillaFileName);
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), gorillaFileName);
	m_layer = m_screen->createLayer(0);
	m_rBackground = m_layer->createRectangle(0, 0, m_screen->getWidth(), m_screen->getHeight());
	m_rBackground->background_image("Ending");
	SoundFactory::getSingleton().playMusic("music/Ending2.wav");
}


LevelEnd::~LevelEnd()
{
}

#include "MainUpdate.h"
bool LevelEnd::update()
{    
	m_time += MainUpdate::getSingleton().getDeltaTime();
	if (m_time > 5.0f)
		m_rBackground->background_image("Ending2");
	return true;
}
