#include "stdafx.h"
#include "MutantShader.h"
#include "../OgreCore/OgreCore.h"


MutantShader::MutantShader() 
{
	init();
}


MutantShader::~MutantShader()
{
}

void MutantShader::init()
{
	/*if (Ogre::RTShader::ShaderGenerator::initialize())
	{
		// Grab the shader generator pointer.
		mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();

		// Add the shader libs resource location.
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation("../media/RTShaderLib", "FileSystem");

		// Set shader cache path.
		mShaderGenerator->setShaderCachePath("../media/shaderCache");

		// Set the scene manager.
		mShaderGenerator->addSceneManager(OgreCore::getSingleton().getSceneMgr());

		// Add a specialized sub-render (per-pixel lighting) state to the default scheme render state
		Ogre::RTShader::RenderState* pMainRenderState = mShaderGenerator->createOrRetrieveRenderState(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME).first;
		pMainRenderState->reset();

		auto shader = static_cast<Ogre::RTShader::FFPFog*>( mShaderGenerator->createSubRenderState(Ogre::RTShader::FFPFog::Type) );
		shader->setFogProperties(Ogre::FogMode::FOG_EXP2, Ogre::ColourValue(1.0, 0.0, 0.0, 1.0), 0.1, 1000.0, 1.0);
		pMainRenderState->addTemplateSubRenderState(shader);

		auto shader1 =  mShaderGenerator->createSubRenderState(Ogre::RTShader::FFPLighting::Type) ;
		pMainRenderState->addTemplateSubRenderState(shader1);

		RTShader::SubRenderState* subRenderState = mShaderGenerator->createSubRenderState(RTShader::NormalMapLighting::Type);
		RTShader::NormalMapLighting* normalMapSubRS = static_cast<RTShader::NormalMapLighting*>(subRenderState);
		normalMapSubRS->setNormalMapSpace(RTShader::NormalMapLighting::NMS_TANGENT);
		normalMapSubRS->setNormalMapTextureName("text");
		pMainRenderState->addTemplateSubRenderState(normalMapSubRS);

		mShaderGenerator->createShaderBasedTechnique("def", Ogre::MaterialManager::DEFAULT_SCHEME_NAME, Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
		mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME, "def");
		OgreCore::getSingleton().getViewport()->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
		m_materialListener = new RTSSDefaultTechniqueListener(mShaderGenerator);
		Ogre::MaterialManager::getSingleton().addListener(m_materialListener);

		MaterialPtr curMaterial = MaterialManager::getSingleton().getByName("def");
		Pass* curPass = curMaterial->getTechnique(0)->getPass(0);
		curPass->setFog(true, Ogre::FogMode::FOG_EXP, Ogre::ColourValue(0.15, 0.1, 0.11, 1.0),0.01);
	}
	else
	{
		for (int i = 0; i < 100; i++)
			cout << "wtf!!" << endl;
	}*/
}
void MutantShader::initIndividual()
{
	// Create shader based technique from the default technique of the given material.
	mShaderGenerator->createShaderBasedTechnique("red", Ogre::MaterialManager::DEFAULT_SCHEME_NAME, Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);

	// Apply the shader generated based techniques.
	OgreCore::getSingleton().getViewport()->setMaterialScheme(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
}