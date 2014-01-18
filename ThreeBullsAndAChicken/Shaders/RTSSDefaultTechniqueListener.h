#pragma once
#include "stdafx.h"
class RTSSDefaultTechniqueListener : public Ogre::MaterialManager::Listener
{
public:
	RTSSDefaultTechniqueListener::RTSSDefaultTechniqueListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator)
	{
		m_ShaderGenerator = pShaderGenerator;
	}
	//---------------------------------------------------------------------------
	virtual RTSSDefaultTechniqueListener::~RTSSDefaultTechniqueListener()
	{
	}
	//-----

	/** This is the hook point where shader based technique will be created.
	It will be called whenever the material manager won't find appropriate technique
	that satisfy the target scheme name. If the scheme name is out target RT Shader System
	scheme name we will try to create shader generated technique for it.
	*/
	virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex,
		const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex,
		const Ogre::Renderable* rend)
	{
		Ogre::Technique* generatedTech = NULL;

		// Case this is the default shader generator scheme.
		if (schemeName == Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME)
		{
			bool techniqueCreated;

			// Create shader generated technique for this material.
			techniqueCreated = m_ShaderGenerator->createShaderBasedTechnique(
				originalMaterial->getName(),
				Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
				schemeName);

			// Case technique registration succeeded.
			if (techniqueCreated)
			{
				// Force creating the shaders for the generated technique.
				m_ShaderGenerator->validateMaterial(schemeName, originalMaterial->getName());

				// Grab the generated technique.
				Ogre::Material::TechniqueIterator itTech = originalMaterial->getTechniqueIterator();

				while (itTech.hasMoreElements())
				{
					Ogre::Technique* curTech = itTech.getNext();

					if (curTech->getSchemeName() == schemeName)
					{
						generatedTech = curTech;
						break;
					}
				}
			}
		}

		return generatedTech;
	}

private:
	Ogre::RTShader::ShaderGenerator*   m_ShaderGenerator;         // The shader generator instance.      


};