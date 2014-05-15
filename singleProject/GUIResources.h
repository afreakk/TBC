#pragma once
#include "OgreSingleton.h"
class RootOverlay : public Ogre::Singleton<RootOverlay>
{
public:
	RootOverlay(const std::string& overlayName);
	~RootOverlay();
	void addOverlayContainer(Ogre::OverlayContainer* container);
	void removeOverlayContainer(Ogre::OverlayContainer* container);
	void show(bool v);
private:
	Ogre::Overlay* m_overlay;
	void createOverlay();
	bool m_isShowing;
	std::string m_overlayName;
};
class GUIResources : public Ogre::Singleton<GUIResources>
{
public:
	GUIResources();
	~GUIResources();
private:
	void loadFont();
};

