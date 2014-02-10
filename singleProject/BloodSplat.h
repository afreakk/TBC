#pragma once
#include "ParticleEffect.h"
namespace ParticleUniverse
{
	class ParticleEmitter;
}
class ModelHandler;
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

