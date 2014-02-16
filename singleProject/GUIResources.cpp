#include "stdafx.h"
#include "GUIResources.h"

template<> GUIResources* Ogre::Singleton<GUIResources>::msSingleton = 0;
GUIResources::GUIResources(std::string overlayName)
: m_overlayName(overlayName)
, m_isShowing(false)
{
	loadFont();
	createOverlay();
}
GUIResources::~GUIResources()
{
}

void GUIResources::loadFont()
{
	FontPtr font = FontManager::getSingleton().getByName("StarWars");
	font.getPointer()->load();
}
void GUIResources::createOverlay()
{
	OverlayManager& overlayManager = OverlayManager::getSingleton();
	m_overlay = overlayManager.create(m_overlayName);
}
void GUIResources::addOverlayContainer(Ogre::OverlayContainer* container)
{
	m_overlay->add2D(container);
}
void GUIResources::removeOverlayContainer(Ogre::OverlayContainer* container)
{
	m_overlay->remove2D(container);
}
void GUIResources::show(bool v)
{
	if (v)
		m_overlay->show();
	else
		m_overlay->hide();
	m_isShowing = v;
}