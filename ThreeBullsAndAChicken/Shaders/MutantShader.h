#pragma once
#include "stdafx.h"
#include "RTSSDefaultTechniqueListener.h"
class MutantShader
{
public:
	MutantShader();
	~MutantShader();
private:
	void init();
	void initIndividual();
	Ogre::RTShader::ShaderGenerator* mShaderGenerator;
	String shaderLibPath;
	RTSSDefaultTechniqueListener* m_materialListener;
};

