#include "stdafx.h"
#include "BehaviourObject.h"
#include "BehaviourState.h"
#include "ModelHandler.h"

BehaviourObject::BehaviourObject(ModelHandler* modelHandler, BObjectType type)
: m_model(modelHandler)
, m_currentState(nullptr)
, m_dead(false)
, m_objectType(type)
, m_selectionPhaseThetaOffset(0.0)
{
}


BehaviourObject::~BehaviourObject()
{
}

void BehaviourObject::update()
{
    m_currentState->update(*m_model.get());
}

void BehaviourObject::setState(BehaviourState* newState)
{
	m_currentState = newState;
	notifySubscribers();
}


//gets
BObjectType BehaviourObject::getObjectType() const
{
	return m_objectType;
}
BEHAVOUR_STATE BehaviourObject::getState() const
{
	return m_currentState->getState();
}
const PolarCoordinates& BehaviourObject::getPolarCoordinates() const
{
	return m_model->getPolarCoordinates();
}
const Ogre::Real BehaviourObject::getSelectionTheta() const
{
	return m_model->getPolarCoordinates().theta + m_selectionPhaseThetaOffset;
}
void BehaviourObject::setSelectionThetaOffset(const Ogre::Real& offset)
{
	m_selectionPhaseThetaOffset = offset;
}
SceneNode* BehaviourObject::getNode() const 
{
	return m_model->getNode();
}
ModelHandler& BehaviourObject::getModelHandler()
{
	return *m_model.get();
}
const ModelHandler& BehaviourObject::getModelHandler() const
{
	return *m_model.get();
}
bool BehaviourObject::isDead() const
{
	return m_dead;
}
//sett
void BehaviourObject::setDead(const bool valu)
{
	m_dead = valu;
}