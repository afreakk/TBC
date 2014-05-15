#pragma once
class LoadingScreenDisplayer
{
public:
	LoadingScreenDisplayer();
	~LoadingScreenDisplayer();
	void animate();
private:
	static Ogre::PanelOverlayElement* s_picture;
	Ogre::Real m_animateValue;

	void initResource();
};

