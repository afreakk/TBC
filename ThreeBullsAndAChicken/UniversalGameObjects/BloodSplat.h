#pragma once
#include "stdafx.h"
#include "ParticleEffect.h"
#include "../ModelBehaviour/ModelHandler.h"
class BloodSplat : public ParticleEffect
{
public:
	BloodSplat(SceneNode* parentNode, ModelHandler* model);
	~BloodSplat();
	void setDirection(Vector3 direction);
	void update() override;
private:
	static int m_bloodSplatCount;
	ModelHandler* m_model;
	ParticleUniverse::ParticleEmitter* m_emitter;
};

