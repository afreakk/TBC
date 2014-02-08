#pragma once
#include "stdafx.h"
#include "ParticleEffect.h"
class MutantFlameThrower : public ParticleEffect
{
public:
	MutantFlameThrower(SceneNode* parentNode);
	~MutantFlameThrower();
private:
	static int m_flameThrowerCount;

};


