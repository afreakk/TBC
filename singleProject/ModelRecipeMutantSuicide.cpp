#include "stdafx.h"
#include "ModelRecipeMutantSuicide.h"
#include "AnimationAttack.h"
#include "AnimationWalk.h"
#include "AnimationDie.h"
#include "OgreCore.h"
#include "AnimationPrepare.h"
#include "AnimationTumble.h"

int ModelRecipeMutantSuicide::s_count = 0;
ModelRecipeMutantSuicide::ModelRecipeMutantSuicide()
: m_id(++s_count)
, m_entityName("MutantSuicide"+boost::lexical_cast<string>(m_id))
, m_nodeName("MutantSuicide"+boost::lexical_cast<string>(m_id))
, m_materialName("Examples/Robot")
, m_hoveredName("HoveredSuicide")
{
}
string anvn = "Walk";
ModelRecipeMutantSuicide::~ModelRecipeMutantSuicide()
{
}

BaseAnimation* ModelRecipeMutantSuicide::getPrepare(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState(anvn)); // doeznthaveitz
	return new AnimationPrepare(anims);
}
Ogre::Entity* ModelRecipeMutantSuicide::initMesh(Ogre::SceneManager* sMgr)
{
	auto resourcePtr =  MeshManager::getSingleton().createOrRetrieve("robot.mesh", "Models") ;
	auto mesh = resourcePtr.first.dynamicCast<Ogre::Mesh>();
	unsigned short src, dest;
	if (!mesh->suggestTangentVectorBuildParams(Ogre::VertexElementSemantic::VES_TANGENT, src,dest))
		mesh->buildTangentVectors(Ogre::VertexElementSemantic::VES_TANGENT,src, dest);
	auto ent = sMgr->createEntity(m_entityName, mesh);
	ent->setUpdateBoundingBoxFromSkeleton(true);
	return ent;
}

const std::string& ModelRecipeMutantSuicide::getMaterialName(const std::string& type)
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
BaseAnimation* ModelRecipeMutantSuicide::getDie(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Die"));
	return new AnimationDie(anims);
}

BaseAnimation* ModelRecipeMutantSuicide::getWalk(Ogre::Entity* entity, Skritt* skritt)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState(anvn));
	return new AnimationWalk(anims, skritt);
}
BaseAnimation* ModelRecipeMutantSuicide::getAttack(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back(entity->getAnimationState("Shoot"));
	return new AnimationAttack(anims);
}
void ModelRecipeMutantSuicide::attachNode(Ogre::SceneNode* node, Ogre::Entity* ent)
{
	auto childNode = node->createChildSceneNode();
    childNode->rotate(Vector3(0.0, 1.0, 0.0), Angle(90.0));
	childNode->scale(Vector3(5.0));
	childNode->attachObject(ent);

}

Ogre::SceneNode* ModelRecipeMutantSuicide::createNode()
{
	return OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode(m_nodeName);
}
BaseAnimation* ModelRecipeMutantSuicide::getTumble(Ogre::Entity* entity)
{
	std::vector<AnimationState*> anims;
	anims.push_back( entity->getAnimationState("Slump") ) ;
	return new AnimationTumble(anims);
}