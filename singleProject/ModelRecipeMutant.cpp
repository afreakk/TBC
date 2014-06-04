#include "stdafx.h"
#include "ModelRecipeMutant.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "AnimationPrepare.h"
#include "OgreCore.h"
#include "AnimationTumble.h"

int ModelRecipeMutant::s_count = 0;
ModelRecipeMutant::ModelRecipeMutant(bool suicide)
: m_id(++s_count)
, m_materialName("enemy_rigg_animasjonEnemy_UVmap_2lambert5")
, m_entityName("MutantRanged"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantRanged"+boost::lexical_cast<string>(m_id))
, m_hoveredName("enemy_fireball_selected")
, m_suicide(suicide)
{
	cout << "MutantEntity: " << m_entityName << endl;
}

ModelRecipeMutant::~ModelRecipeMutant()
{
	cout << "mutant recipe destrucotr" << endl;
}

Ogre::Entity* ModelRecipeMutant::initMesh(Ogre::SceneManager* sMgr)
{
	auto resourcePtr =  MeshManager::getSingleton().createOrRetrieve("monster.mesh", "Models") ;
	auto mesh = resourcePtr.first.dynamicCast<Ogre::Mesh>();
	unsigned short src, dest;
	if (!mesh->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		mesh->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	auto ent = sMgr->createEntity(m_entityName, mesh);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	ent->setMaterialName( m_suicide ? "suzide" :  m_materialName);
//	ent->getMesh()->buildEdgeList();
	return ent;
}

BaseAnimation* ModelRecipeMutant::getPrepare(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("monster"));
	return new AnimationPrepareMonster(anims);
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
	anims.push_back(entity->getAnimationState("monster"));
	return new AnimationDieMonster(anims);
}

BaseAnimation* ModelRecipeMutant::getWalk(Ogre::Entity* entity, Skritt* skritt)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("monster"));
	return new AnimationWalkMonster(anims, skritt);
}
BaseAnimation* ModelRecipeMutant::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("monster"));
	return new AnimationAttackMonster(anims);
}
void ModelRecipeMutant::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	auto entNode = node->createChildSceneNode();
	entNode->attachObject(ent);
	entNode->setScale(Vector3( m_suicide ? 30.0f : 40.0f));
	entNode->translate(Vector3(0, 0, 0));
	entNode->rotate(Vector3::UNIT_Y, Ogre::Radian(Math::PI));
}

Ogre::SceneNode* ModelRecipeMutant::createNode()
{
	return OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode(m_nodeName);
}
BaseAnimation* ModelRecipeMutant::getTumble(Ogre::Entity* entity, Skritt* skritt)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("monster"));
	return new AnimationWalkMonster(anims, skritt);
}