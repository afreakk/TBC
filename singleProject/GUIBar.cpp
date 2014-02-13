#include "stdafx.h"
#include "BarTypes.h"
#include "boost/lexical_cast.hpp"
#include "OgreCore.h"
#include "MovableText.h"
#include "GUIResources.h"

static const std::string fontName = "StarWars";



unsigned GUIBar::m_count = 0;
GUIBar::GUIBar( Ogre::Real xPos, Ogre::Real yPos, Ogre::Real barWidth, Ogre::Real barHeight, std::string materialName)
: m_barMaterial(materialName)
, m_rammeMaterial("ramme")
, m_glassMaterial("glass")
, m_barMaxWidth(barWidth)
, m_barHeight(barHeight)
, m_xPos(xPos)
, m_yPos(yPos)
, m_id(" Count: "+boost::lexical_cast<std::string>(++m_count))
{
	setupBar();
}
GUIBar::~GUIBar()
{

}
void GUIBar::setValue(unsigned energy)
{
//	m_text->setCaption( boost::lexical_cast<string>(energy) ) ;
	updateBar(energy);
}

void GUIBar::updateBar(unsigned energy)
{
	Real rEnergy = static_cast<Real>(energy);
	m_bar->setDimensions(m_barMaxWidth*( rEnergy/100.0),m_barHeight);
	m_bar->setPosition((100.0-rEnergy)/5000.0, 0);
}
void GUIBar::setupBar()
{
	m_ramme = static_cast<OverlayContainer*>(OverlayManager::getSingleton().createOverlayElement("Panel", "ramme" + m_id));
	m_ramme->setMaterialName(m_rammeMaterial);
	m_ramme->setPosition(m_xPos, m_yPos);
	m_ramme->setDimensions(m_barMaxWidth, m_barHeight);

	m_bar = OverlayManager::getSingleton().createOverlayElement("Panel", "bar"+m_id) ;
	m_bar->setMaterialName(m_barMaterial);
	m_bar->setDimensions(m_barMaxWidth, m_barHeight);
	m_ramme->addChild(m_bar);

    m_glass = OverlayManager::getSingleton().createOverlayElement("Panel", "glass"+m_id) ;
	m_glass->setMaterialName(m_glassMaterial);
	m_glass->setDimensions(m_barMaxWidth, m_barHeight);
	static_cast<OverlayContainer*>(m_ramme)->addChild(m_glass);

	GUIResources::getSingleton().addOverlayContainer(m_ramme);
}
void GUIBar::initText(Ogre::OverlayContainer* parent)
{
	m_text = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "text"+m_id));
	m_text->setMetricsMode(Ogre::GuiMetricsMode::GMM_PIXELS);
	m_text->setPosition(m_barMaxWidth/2.0, m_barHeight/2.0);
	m_text->setCharHeight(12);
	m_text->setFontName(fontName);
	m_text->setColourBottom(ColourValue(0.3, 0.5, 0.3));
	m_text->setColourTop(ColourValue(0.5, 0.7, 0.5));
	parent->addChild(m_text);
}