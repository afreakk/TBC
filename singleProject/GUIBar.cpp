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
, m_dynamicBarMarkerMaterial(materialName + "Marker")
, m_rammeMaterial("ramme")
, m_glassMaterial("glass")
, m_ramme(nullptr)
, m_dynamicBar(nullptr)
, m_barMarker(nullptr)
, m_glass(nullptr)
, m_text(nullptr)
, m_barMaxWidth(barWidth)
, m_barHeight(barHeight)
, m_xPos(xPos)
, m_yPos(yPos)
, m_dynamicBarScaleX(0.0)
, m_id(" Count: "+boost::lexical_cast<std::string>(++m_count))
, m_energy(0)
{
	setupBar();
}
GUIBar::~GUIBar()
{
	if (m_ramme)
		GUIResources::getSingleton().removeOverlayContainer(m_ramme);
}
void GUIBar::setValue(unsigned energy)
{
	m_energy = energy;
	updateBar(energy);
//	m_text->setCaption( boost::lexical_cast<string>(energy) ) ;
}

void GUIBar::markBar(unsigned newEnergy)
{
	if (newEnergy == 0 || newEnergy > m_energy)
	{
		m_barMarker->hide();
		return;
	}
	m_barMarker->show();
	Real normalised = boost::numeric_cast<Real, unsigned>(newEnergy)/ 100.0;
	Real markerBarScaleX = normalised*m_barMaxWidth;
    Real xPos = m_dynamicBarScaleX-markerBarScaleX;
	while (xPos + markerBarScaleX > m_barMaxWidth-0.01)
		xPos -= 0.001;
	m_barMarker->setPosition(xPos, 0);
	m_barMarker->setDimensions(markerBarScaleX,m_barHeight);
	m_barMarker->setUV(0.0+normalised/2.0, 0.0, 1.0-normalised/2.0, 1.0);
}
void GUIBar::updateBar(unsigned energy)
{
	Real normalised = boost::numeric_cast<Real, unsigned>(energy) / 100.0;
	m_dynamicBarScaleX = normalised*m_barMaxWidth;
	m_dynamicBar->setDimensions(m_dynamicBarScaleX,m_barHeight);
	m_dynamicBar->setUV(0.0, 0.0, normalised, 1.0);
}
void GUIBar::setupBar()
{
	m_ramme = static_cast<PanelOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Panel", "ramme" + m_id));
	m_ramme->setMaterialName(m_rammeMaterial);
	m_ramme->setPosition(m_xPos, m_yPos);
	m_ramme->setDimensions(m_barMaxWidth, m_barHeight);

	m_dynamicBar = static_cast<PanelOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Panel", "bar"+m_id) );
	m_dynamicBar->setMaterialName(m_barMaterial);
	m_dynamicBar->setDimensions(m_barMaxWidth, m_barHeight);
	m_ramme->addChild(m_dynamicBar);

	m_barMarker = static_cast<PanelOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Panel", "barMarker" + m_id) );
	m_barMarker->setMaterialName(m_dynamicBarMarkerMaterial);
	m_barMarker->setDimensions(0, m_barHeight);
	static_cast<OverlayContainer*>(m_ramme)->addChild(m_barMarker);

    m_glass = static_cast<PanelOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Panel", "glass"+m_id) );
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