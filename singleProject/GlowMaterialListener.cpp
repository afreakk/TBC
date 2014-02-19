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
Ogre::Technique* GlowMaterialListener::handleSchemeNotFound(unsigned short, const Ogre::String& schemeName, Ogre::Material*mat, unsigned short, const Ogre::Renderable*)
{
    if (schemeName == "glow")
    {
        return mBlackMat->getTechnique(0);
    }
    return NULL;
}