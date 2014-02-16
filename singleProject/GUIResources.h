#pragma once
#include "OgreSingleton.h"
class GUIResources : public Ogre::Singleton<GUIResources>
{
public:
	GUIResources(std::string overlayName);
	~GUIResources();
	void addOverlayContainer(Ogre::OverlayContainer* container);
	void removeOverlayContainer(Ogre::OverlayContainer* container);
	void show(bool v);
private:
	void loadFont();
	void createOverlay();
	bool m_isShowing;
	Ogre::Overlay* m_overlay;
	std::string m_overlayName;
};

