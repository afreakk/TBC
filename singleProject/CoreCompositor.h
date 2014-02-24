#pragma once
#include "OgreSingleton.h"
class GlowMaterialListener;
class CoreCompositor : public Ogre::Singleton<CoreCompositor>
{
public:
	CoreCompositor(Ogre::Viewport* viewport);
	void blackAndWhite(bool enabled);
private:
	Ogre::Viewport* m_vp;
	std::unique_ptr<GlowMaterialListener> gml;
};