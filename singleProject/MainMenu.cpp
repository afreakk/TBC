#include "stdafx.h"
#include "MainMenu.h"
#include "OgreCore.h"

MainMenu::MainMenu()
{
	m_screen = Gorilla::Silverback::getSingleton().createScreen(OgreCore::getSingleton().getViewport(), "dejavu");
	Ogre::Real vpW = m_screen->getWidth(), vpH = m_screen->getHeight();

	// Create our drawing layer
	m_layer = m_screen->createLayer(0);
	m_rect = m_layer->createRectangle(0, 0, vpW, vpH);
	m_rect->background_gradient(Gorilla::Gradient_Diagonal, Gorilla::rgb(98, 0, 63), Gorilla::rgb(255, 180, 174));


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
