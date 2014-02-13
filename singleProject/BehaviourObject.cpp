#include "stdafx.h"
#include "BehaviourObject.h"
#include "BehaviourState.h"
#include "ModelHandler.h"

BehaviourObject::BehaviourObject(ModelHandler* modelHandler)
: m_model(modelHandler)
, m_currentState(nullptr)
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
BEHAVOUR_STATE BehaviourObject::getState() const
{
	return m_currentState->getState();
}
PolarCoordinates BehaviourObject::getNormalPosition() 
{
	return m_model->getNormalPos();
}
SceneNode* BehaviourObject::getNode() const 
{
	return m_model->getNode();
}
ModelHandler& BehaviourObject::getModelHandler()
{
	return *m_model.get();
}