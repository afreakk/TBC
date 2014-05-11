#include "stdafx.h"
#include "MainMenuButton.h"

Gorilla::Colours::Colour MainMenuButton::s_inactiveColor = Gorilla::Colours::Gray;
Gorilla::Colours::Colour MainMenuButton::s_activeColour = Gorilla::Colours::Snow;
MainMenuButton::MainMenuButton(Gorilla::Layer* layer, Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height, std::string spriteName, 
	ButtonType buttonType)
: m_rectangle ( layer->createRectangle(left,top, width, height) ) 
, m_btnType(buttonType)
{

	m_spriteNames.push_back(spriteName);
	m_currentSpriteName = m_spriteNames.begin();

	m_rectangle->background_image(*m_currentSpriteName);
    m_rectangle->background_colour(s_inactiveColor);
}

void MainMenuButton::animateClick()
{
	if (m_spriteNames.size() > 1)
	{
		if (m_currentSpriteName != --m_spriteNames.end() )
			m_currentSpriteName++;
		else
			m_currentSpriteName = m_spriteNames.begin();
		m_rectangle->background_image(*m_currentSpriteName);
	}
}
void MainMenuButton::addSpriteName(const std::string& spriteName)
{
	m_spriteNames.push_back(spriteName);
	m_currentSpriteName = m_spriteNames.begin();
}
MainMenuButton::~MainMenuButton()
{
}

ButtonType MainMenuButton::getType()
{
	return m_btnType;
}
void MainMenuButton::selected(bool selected)
{
	if (selected)
		m_rectangle->background_colour(s_activeColour);
	else
		m_rectangle->background_colour(s_inactiveColor);
}
