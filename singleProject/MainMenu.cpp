#include "stdafx.h"
#include "MainMenu.h"
#include "OgreCore.h"
MainMenu::MainMenu()
{
    Gorilla::Silverback::getSingleton().loadAtlas("menu");
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "menu");
	Ogre::Real vpW = m_screen->getWidth(), vpH = m_screen->getHeight();

	// Create our drawing layer
	m_layer = m_screen->createLayer(0);
	m_rBackground = m_layer->createRectangle(0, 0, vpW, vpH);
	m_rBackground->background_image("background");
	Real width = vpW / 4.0f;
	Real height = vpH / 10.0f;
	Real xPos = vpW / 2.0f - width / 2.0f;

	m_rPlay = m_layer->createRectangle(xPos,    vpH / 2.0f, width, height);
	m_rOptions = m_layer->createRectangle(xPos, vpH / 2.0f+height*1.5f, width, height);
    m_rQuit = m_layer->createRectangle(xPos,    vpH / 2.0f+height*3.0f, width, height);

	m_rPlay->background_image("play");
	m_rOptions->background_image("options");
	m_rQuit->background_image("quit");

/*	markup = m_layer->createMarkupText(9, 5, 5, "%@24%A Haiku\n%@14%Written by Betajaen%@9%\nSo many to choose from\nPretty typefaces on Ogre screen\nTime to update Git");

	caption = m_layer->createCaption(9, vpW - 55, 5, "9");
	caption->width(50);
	caption->align(Gorilla::TextAlign_Right);

	caption = m_layer->createCaption(14, vpW - 55, 18, "14");
	caption->width(50);
	caption->align(Gorilla::TextAlign_Right);

	caption = m_layer->createCaption(24, vpW - 55, 33, "24");
	caption->width(50);
	caption->align(Gorilla::TextAlign_Right);*/

}


MainMenu::~MainMenu()
{
	Gorilla::Silverback::getSingleton().destroyScreen(m_screen);
}
