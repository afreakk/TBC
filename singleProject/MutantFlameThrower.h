#pragma once
#include "ParticleEffect.h"
#include "ModelHandler.h"
class MutantFlameThrower : public ParticleEffect
{
public:
	MutantFlameThrower(SceneNode* parentNode, ModelHandler* model);
	~MutantFlameThrower();
	void update() override;
private:
	static int m_flameThrowerCount;
	ModelHandler* m_model;
	ParticleUniverse::ParticleEmitter* m_emitter;

};


