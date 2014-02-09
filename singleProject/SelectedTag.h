#pragma once
#include "ParticleUniverseSystemManager.h"
class SelectedTag
{
public:
	SelectedTag(SceneNode* parentNode);
	~SelectedTag();
	void select();
private:
	static int m_selectedTagCount;
	const int m_id;
	ParticleUniverse::ParticleSystem* m_particleSystem;
	SceneNode* m_node;
};

