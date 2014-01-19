#include "stdafx.h"
#include "UniversalModelHandler.h"
#include "boost\lexical_cast.hpp"

using namespace Ogre;


UniversalModelHandler::UniversalModelHandler(CreationRecipes* recipe)
: m_entity(nullptr), m_node(nullptr)
, m_walkAnim(nullptr), m_attackAnim(nullptr)
, m_crRecipe(recipe)
{
}
UniversalModelHandler::~UniversalModelHandler()
{
}

void UniversalModelHandler::playWalkAnim(const Real howMuch)
{
	enableAnimation(m_walkAnim);
	m_walkAnim->addTime(howMuch);
}
void UniversalModelHandler::normalWalk(const Ogre::Real& rInc, const NormalDirection& activeDirection)
{
	enableAnimation(m_walkAnim);
	m_walkAnim->addTime(Ogre::Math::Abs(rInc)*20.0);
	m_normalPosition.r += rInc;
	UnitCircleMovement::normalSetDirection(m_node, getNormalPos(), activeDirection);
	UnitCircleMovement::normalSetPosition(m_node, getNormalPos());
}
//private
void UniversalModelHandler::enableAnimation(AnimationState* anim)
{
		anim->setEnabled(true);
}
void UniversalModelHandler::init(NormalPosition pos) 
{
	SceneManager* sMgr = OgreCore::getSingletonPtr()->getSceneMgr();

	m_entity		= m_crRecipe->initMesh(sMgr);

	m_attackAnim	= m_crRecipe->getAttack(m_entity);
	m_walkAnim		= m_crRecipe->getWalk(m_entity);

	m_node			= m_crRecipe->initNode(sMgr);
	m_node->attachObject(m_entity);

	UnitCircleMovement::normalSetPosition(m_node, pos);
	m_normalPosition = pos;
}

Ogre::SceneNode* UniversalModelHandler::getNode() const 
{
	return m_node;
}
const NormalPosition& UniversalModelHandler::getNormalPos() 
{
	return m_normalPosition;
}

const Vector3 UniversalModelHandler::getNormalVecPos() const
{
	return UnitCircleMovement::posFromR(m_normalPosition);
}

Entity* UniversalModelHandler::getEntity() const
{
	return m_entity;
}
string UniversalModelHandler::getMaterial() const
{
	return m_materialName;
}
void UniversalModelHandler::setNormalPos(NormalPosition newPos)
{
	m_normalPosition = newPos;
}