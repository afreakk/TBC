
#pragma once
#include "ParticleUniverseSystemManager.h"
class SlowMotionParticle
{
public:
	SlowMotionParticle(SceneNode* parentNode);
	~SlowMotionParticle();
	void select(bool enabled);
private:
	static int m_selectedTagCount;
	const int m_id;
	ParticleUniverse::ParticleSystem* m_particleSystem;
	SceneNode* m_node;
};
class TeleportParticle
{
public:
	TeleportParticle(SceneNode* parentNode);
	~TeleportParticle();
	void select(bool enabled);
private:
	static int m_selectedTagCount;
	const int m_id;
	ParticleUniverse::ParticleSystem* m_particleSystem;
	SceneNode* m_node;
};