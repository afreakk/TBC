#include "stdafx.h"
#include "LightHandler.h"
#include "../OgreCore/OgreCore.h"

LightHandler::LightHandler()
{

	auto sMgr = OgreCore::getSingletonPtr()->getSceneMgr();
	/*
	sMgr->setShadowTextureSelfShadow(true);
	// Set the caster material which uses the shaders defined above
	sMgr->setShadowTextureCasterMaterial("Ogre/DepthShadowmap/Caster/Float");
	// Set the pixel format to floating point
	sMgr->setShadowTexturePixelFormat(Ogre::PF_FLOAT32_R);
	// You can switch this on or off, I suggest you try both and see which works best for you
	sMgr->setShadowCasterRenderBackFaces(true);
	// Finally enable the shadows using texture additive integrated
	sMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE_INTEGRATED);
	sMgr->setShadowTextureSize(2048*2);*/
	sMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* directionalLight = sMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(Ogre::ColourValue(.5, .5, .5));
	directionalLight->setSpecularColour(Ogre::ColourValue(.5, .5, .5));
	directionalLight->setDirection(Ogre::Vector3(-1, -1, -1));


}


LightHandler::~LightHandler()
{
}
