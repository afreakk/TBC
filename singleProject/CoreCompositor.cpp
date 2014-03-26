#include "stdafx.h"
#include "CoreCompositor.h"
#include "OgreCore.h"
#include "GlowMaterialListener.h"
#include "HDRCompositor.h"
template<> CoreCompositor* Ogre::Singleton<CoreCompositor>::msSingleton = 0;
CoreCompositor::CoreCompositor(Ogre::Viewport* viewport)
: m_vp(viewport)
, m_HDRComp(new HDRCompositor(OgreCore::getSingleton().getWindow(),OgreCore::getSingleton().getCamera()))
{
	gml = unique_ptr<GlowMaterialListener>(new GlowMaterialListener());
    Ogre::MaterialManager::getSingleton().addListener(gml.get());
    CompositorManager::getSingleton().addCompositor(m_vp, "B&W");
	CompositorManager::getSingleton().addCompositor(m_vp, "blurStuff");
	CompositorManager::getSingleton().setCompositorEnabled(m_vp, "blurStuff", true);
}
void CoreCompositor::initHDR()
{
/*	CompositorManager::getSingleton().addCompositor(m_camera->getViewport(), "Glow");
	CompositorManager::getSingleton().setCompositorEnabled(m_camera->getViewport(), "Glow", true);
	GlowMaterialListener *gml = new GlowMaterialListener();
	Ogre::MaterialManager::getSingleton().addListener(gml);*/
/*	m_HDRComp->SetToneMapper(HDRCompositor::TONEMAPPER::TM_REINHARDSMOD);
	m_HDRComp->SetStarPasses(2);
	m_HDRComp->SetGlarePasses(2);
	m_HDRComp->SetGlareType(HDRCompositor::GLARETYPE::GT_BLUR);
	m_HDRComp->SetStarType(HDRCompositor::STARTYPE::ST_CROSS);
	m_HDRComp->SetAutoKeying(true);
	m_HDRComp->SetKey(0.2);
	m_HDRComp->SetLumAdapdation(true);
	m_HDRComp->SetAdaptationScale(10);
	m_HDRComp->SetGlareStrength(0.5f);
	m_HDRComp->SetStarStrength(0.5f);
	m_HDRComp->Enable(true);*/
}
void CoreCompositor::blackAndWhite(bool enabled)
{
	CompositorManager::getSingleton().setCompositorEnabled(m_vp, "B&W", enabled);
}