#include "stdafx.h"
#include "MainMenuButton.h"


MainMenuButton::MainMenuButton(Gorilla::Layer* layer, Ogre::Real left, Ogre::Real top, Ogre::Real width, Ogre::Real height, std::string name)
: m_rectangle ( layer->createRectangle(left,top, width, height) ) 
{
	m_rectangle->background_image(name);
    m_rectangle->background_colour(Gorilla::Colours::LimeGreen);
}

MainMenuButton::~MainMenuButton()
{
}

void MainMenuButton::selected(bool selected)
{
	if (selected)
		m_rectangle->background_colour(Gorilla::Colours::Azure);
	else
		m_rectangle->background_colour(Gorilla::Colours::LimeGreen);
}
