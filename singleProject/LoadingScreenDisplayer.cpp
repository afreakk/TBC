#include "stdafx.h"
#include "LoadingScreenDisplayer.h"
#include "OgreCore.h"
#include "GUIResources.h"
Ogre::PanelOverlayElement* LoadingScreenDisplayer::s_picture = nullptr;

LoadingScreenDisplayer::LoadingScreenDisplayer()
: m_animateValue(0.0f)
{
	initResource();
	RootOverlay::getSingleton().addOverlayContainer(s_picture);
}
static Ogre::Real ANIMATEINCREMENT = 0.1f;

void LoadingScreenDisplayer::animate()
{
	m_animateValue += ANIMATEINCREMENT;
	assert(s_picture);
		auto mat = s_picture->getMaterial();
		auto techniq = mat->getTechnique(0);
		auto pass = techniq->getPass(0);
		auto fragParams = pass->getFragmentProgramParameters();
		fragParams->setNamedConstant("animate", m_animateValue);
}
LoadingScreenDisplayer::~LoadingScreenDisplayer()
{
	RootOverlay::getSingleton().removeOverlayContainer(s_picture);
}

void LoadingScreenDisplayer::initResource()
{
	if (s_picture)
		return;
    s_picture = static_cast<PanelOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Panel", "loadingScreenOverlay") );
	s_picture->setMaterialName("loadingScreenMaterial");
	s_picture->setDimensions(1.0f,1.0f);
}