#include "stdafx.h"
#include "ModelRecipeMutant.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "AnimationPrepare.h"
#include "OgreCore.h"
#include "AnimationTumble.h"

int ModelRecipeMutant::s_count = 0;
ModelRecipeMutant::ModelRecipeMutant()
: m_id(++s_count)
, m_materialName("NinjaEnemy")
, m_entityName("MutantRanged"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantRanged"+boost::lexical_cast<string>(m_id))
, m_hoveredName("HoveredRanged")
{
	cout << "MutantEntity: " << m_entityName << endl;
}

ModelRecipeMutant::~ModelRecipeMutant()
{
	cout << "mutant recipe destrucotr" << endl;
}

Ogre::Entity* ModelRecipeMutant::initMesh(Ogre::SceneManager* sMgr)
{
	auto resourcePtr =  MeshManager::getSingleton().createOrRetrieve("ninja.mesh", "Models") ;
	auto mesh = resourcePtr.first.dynamicCast<Ogre::Mesh>();
	unsigned short src, dest;
	if (!mesh->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		mesh->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	auto ent = sMgr->createEntity(m_entityName, mesh);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	ent->setMaterialName(m_materialName);
	return ent;
}

BaseAnimation* ModelRecipeMutant::getPrepare(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Stealth"));
	return new AnimationPrepare(anims);
}
const std::string& ModelRecipeMutant::getMaterialName(const std::string& type)
{
	if (type == "default")
		return m_materialName;
	else if (type == "hovered")
		return m_hoveredName;
	else if (type == "selected")
		return m_hoveredName;
	assert(0);
	return "error";
}
BaseAnimation* ModelRecipeMutant::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Death1"));
	anims.push_back(entity->getAnimationState("Death2"));
	return new AnimationDie(anims);
}

BaseAnimation* ModelRecipeMutant::getWalk(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Walk"));
	return new AnimationWalk(anims);
}
BaseAnimation* ModelRecipeMutant::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Attack1"));
	anims.push_back(entity->getAnimationState("Attack2"));
	anims.push_back(entity->getAnimationState("Attack3"));
	return new AnimationAttack(anims);
}
void ModelRecipeMutant::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	node->attachObject(ent);
}

Ogre::SceneNode* ModelRecipeMutant::createNode()
{
	return OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode(m_nodeName);
}
BaseAnimation* ModelRecipeMutant::getTumble(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("Backflip") ) ;
	return new AnimationTumble(anims);
}