#pragma once
#include "stdafx.h"
#include "ParticleUniverseSystemManager.h"
class BloodSplat
{
public:
	BloodSplat(SceneNode* parentNode);
	~BloodSplat();
	void activate(Real timeScale);
private:
	static int m_bloodSplatCount;
	const int m_id;
	ParticleUniverse::ParticleSystem* m_particleSystem;
	SceneNode* m_node;
	bool m_ran;
};

