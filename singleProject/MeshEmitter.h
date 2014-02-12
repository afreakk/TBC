#pragma once
#include "ParticleEffect.h"
namespace ParticleUniverse
{
	class MeshSurfaceEmitter;
}
class MeshEmitter :	public ParticleEffect
{
public:
	MeshEmitter(SceneNode* parentNode, string name,string templateName, Ogre::Entity* entity);
	virtual ~MeshEmitter();
	virtual void update() override;
private:
	static unsigned m_count;
	const int m_id;
	ParticleUniverse::MeshSurfaceEmitter* m_meshEmitter;
	Ogre::Entity* m_entity;
};

class BloodMesh : public MeshEmitter
{
public:
	BloodMesh(Ogre::Entity* entity)
	:MeshEmitter(static_cast<SceneNode*>(entity->getParentNode()), "bloodMeshTest", "bloodmesh", entity)
	{
	}

};