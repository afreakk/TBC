#include "stdafx.h"
#include "GlowMaterialListener.h"
#include "MainUpdate.h"

GlowMaterialListener::GlowMaterialListener()
{
    mBlackMat = Ogre::MaterialManager::getSingleton().create("mGlowBlack", "Internal");
    mBlackMat->getTechnique(0)->getPass(0)->setDiffuse(0, 0, 0, 0);
    mBlackMat->getTechnique(0)->getPass(0)->setSpecular(0, 0, 0, 0);
    mBlackMat->getTechnique(0)->getPass(0)->setAmbient(0, 0, 0);
    mBlackMat->getTechnique(0)->getPass(0)->setSelfIllumination(0, 0, 0);
}
static std::string particleMaterialPrefix = "mp_";
static std::string gorillaMat = "Gorilla3D";
Ogre::Technique* GlowMaterialListener::handleSchemeNotFound(unsigned short, const Ogre::String& schemeName, Ogre::Material*mat, unsigned short, const Ogre::Renderable* rndr)
{
    if (schemeName == "blood")
    {
		if ((mat->getName().compare(0, particleMaterialPrefix.length(), particleMaterialPrefix) == 0) || mat->getName() == "HoveredSuicide" 
			|| mat->getName() == "HoveredRanged"||mat->getName()=="wooshMat"||mat->getName()=="PUMediaPack/Watch"||mat->getName() =="selectionLine")
		    return NULL;
        return mBlackMat->getTechnique(0);
    }
	else if (schemeName == "blur")
	{
		if ((mat->getName().compare(0, particleMaterialPrefix.length(), particleMaterialPrefix) == 0) || mat->getName() == "HoveredSuicide" 
			|| mat->getName() == "HoveredRanged"||mat->getName()=="wooshMat"||mat->getName()=="PUMediaPack/Watch"||mat->getName() =="selectionLine")
		    return NULL;
        return mBlackMat->getTechnique(0);
	}
	else if (schemeName == "tooltip")
	{
		if (mat->getName().compare(0, gorillaMat.length(), gorillaMat) == 0)
			return NULL;
        return mBlackMat->getTechnique(0);
	}
    return NULL;
}