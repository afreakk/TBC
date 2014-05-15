#include "stdafx.h"
#include "GUIResources.h"

template<> RootOverlay* Ogre::Singleton<RootOverlay>::msSingleton = 0;

RootOverlay::RootOverlay(const std::string& overlayName)
: m_overlayName(overlayName)
, m_isShowing(false)
{
	createOverlay();
}

RootOverlay::~RootOverlay()
{

}

void RootOverlay::createOverlay()
{
	OverlayManager& overlayManager = OverlayManager::getSingleton();
	m_overlay = overlayManager.create(m_overlayName);
}
void RootOverlay::show(bool v)
{
	if (v)
		m_overlay->show();
	else
		m_overlay->hide();
	m_isShowing = v;
}
void RootOverlay::addOverlayContainer(Ogre::OverlayContainer* container)
{
	m_overlay->add2D(container);
}
void RootOverlay::removeOverlayContainer(Ogre::OverlayContainer* container)
{
	m_overlay->remove2D(container);
}
template<> GUIResources* Ogre::Singleton<GUIResources>::msSingleton = 0;
GUIResources::GUIResources()
{
	loadFont();
}
GUIResources::~GUIResources()
{
}

void GUIResources::loadFont()
{
	FontPtr font = FontManager::getSingleton().getByName("StarWars");
	font.getPointer()->load();
}
