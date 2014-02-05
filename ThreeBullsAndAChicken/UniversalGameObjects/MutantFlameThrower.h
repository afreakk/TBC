#pragma once
#include "stdafx.h"
#include "ParticleUniverseSystemManager.h"
class MutantFlameThrower
{
public:
	MutantFlameThrower(SceneNode* parentNode);
	~MutantFlameThrower();
	void activate(Real timeScale);
private:
	static int m_flameThrowerCount;
	const int m_id;
	ParticleUniverse::ParticleSystem* m_particleSystem;
	SceneNode* m_node;
	bool m_ran;

};


