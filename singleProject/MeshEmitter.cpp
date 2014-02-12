#include "stdafx.h"
#include "MeshEmitter.h"
#include "OgreCore.h"
#include "ParticleEmitters/ParticleUniverseMeshSurfaceEmitter.h"
unsigned MeshEmitter::m_count = 0;
MeshEmitter::MeshEmitter(SceneNode* parentNode, string name,string templateName, Ogre::Entity* entity)
: ParticleEffect(parentNode,++m_count,name,templateName,OgreCore::getSingleton().getSceneMgr())
, m_id(m_count)
, m_entity(entity)
{
	m_meshEmitter = static_cast<ParticleUniverse::MeshSurfaceEmitter*>(m_particleSystem->getTechnique(0)->getEmitter("meshEmitter"));
}
void MeshEmitter::update()
{
	ParticleEffect::update();

}

MeshEmitter::~MeshEmitter()
{
}
