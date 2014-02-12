#include "stdafx.h"
#include "BarTypes.h"
#include "boost/lexical_cast.hpp"
#include "OgreCore.h"
#include "MovableText.h"
#include "GUIResources.h"

static const std::string fontName = "StarWars";



unsigned GUIBar::m_count = 0;
GUIBar::GUIBar( Ogre::Real xPos, Ogre::Real yPos, Ogre::Real barWidth, Ogre::Real barHeight, std::string materialName)
: m_resolution(OgreCore::getSingleton().getResolution())
, m_materialName(materialName)
, m_barMaxWidth(barWidth*m_resolution.x)
, m_barHeight(barHeight*m_resolution.y)
, m_xPos(xPos*m_resolution.x)
, m_yPos(yPos*m_resolution.y)
, m_id(" Count: "+boost::lexical_cast<std::string>(++m_count))
{
	setupBar();
}
GUIBar::~GUIBar()
{

}
void GUIBar::setValue(unsigned energy)
{
	m_text->setCaption( boost::lexical_cast<string>(energy) ) ;
	m_bar->setDimensions(m_barMaxWidth*( static_cast<Real>( energy)/100.0),m_barHeight);
}

void GUIBar::setupBar()
{

	m_bar = static_cast<OverlayContainer*>(OverlayManager::getSingleton().createOverlayElement("Panel", "bar"+m_id) );
	m_bar->setMetricsMode(Ogre::GMM_PIXELS);
	m_bar->setPosition(m_xPos, m_yPos);
	m_bar->setDimensions(m_barMaxWidth, m_barHeight);
	m_bar->setMaterialName(m_materialName);

	m_text = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "text"+m_id));
	m_text->setMetricsMode(Ogre::GMM_PIXELS);
	m_text->setPosition(0, 0);
	m_text->setDimensions(200, 100);
	m_text->setCharHeight(32);
	m_text->setFontName(fontName);
	m_text->setColourBottom(ColourValue(0.3, 0.5, 0.3));
	m_text->setColourTop(ColourValue(0.5, 0.7, 0.5));

	m_bar->addChild(m_text);

	GUIResources::getSingleton().addOverlayContainer(m_bar);
}