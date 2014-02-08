#include "stdafx.h"
#include "PlayerGUIStyle.h"
#include "boost/lexical_cast.hpp"
#include "../OgreCore/OgreCore.h"
#include "../Other/MovableText.h"
PlayerGUIStyle::PlayerGUIStyle() : m_energyBar(nullptr), m_energyHeight(0.0), m_energyMaxWidth(0.0), m_energyText(nullptr), m_overlay(nullptr)
{
	loadFont();
	setupEnergyGUI();
	setEnergy(100);
}
void PlayerGUIStyle::loadFont()
{
	FontPtr font = FontManager::getSingleton().getByName("StarWars");
	font.getPointer()->load();
}

PlayerGUIStyle::~PlayerGUIStyle()
{
}

void PlayerGUIStyle::setupEnergyGUI()
{

	Vector2 scrRes = OgreCore::getSingleton().getResolution();
	Real xPos = scrRes.x / (8.0 * (16.0/9.0));
	Real yPos = scrRes.y - scrRes.y / 8.0;

	m_energyMaxWidth = scrRes.x/4.0;
	m_energyHeight	 = scrRes.y/16.0;

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	m_overlay = overlayManager.create("OverlayName");

	m_energyBar = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", "PanelName"));
	m_energyBar->setMetricsMode(Ogre::GMM_PIXELS);
	m_energyBar->setPosition(xPos,yPos );
	m_energyBar->setDimensions(m_energyMaxWidth, m_energyHeight);
//	m_energyBar->setMaterialName("def");


	m_energyText = static_cast<TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", "TextAreaName"));
	m_energyText->setMetricsMode(Ogre::GMM_PIXELS);
	m_energyText->setPosition(0, 0);
	m_energyText->setDimensions(200, 100);
	m_energyText->setCharHeight(32);
	m_energyText->setFontName("StarWars");
	m_energyText->setColourBottom(ColourValue(0.3, 0.5, 0.3));
	m_energyText->setColourTop(ColourValue(0.5, 0.7, 0.5));

	m_energyBar->addChild(m_energyText);

	m_overlay->add2D(m_energyBar);

	m_overlay->show();
}
void PlayerGUIStyle::setEnergy(int energy)
{
	cout << boost::lexical_cast<string>(energy) << "isEnergyNow"<< endl;
	m_energyText->setCaption( boost::lexical_cast<string>(energy) ) ;
	m_energyBar->setDimensions(m_energyMaxWidth*( static_cast<Real>( energy)/100.0),m_energyHeight);
}