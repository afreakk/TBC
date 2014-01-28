#include "stdafx.h"
#include "BehaviourObject.h"


BehaviourObject::BehaviourObject(UniversalModelHandler* modelHandler)
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

//subscriberStuff
void BehaviourObject::addSubsriber(BehaviourStateSubscriber* subscriber, string id)
{
	m_stateSubsribers[id] = subscriber;
	m_stateSubsribers[id]->notify(getState());
}
void BehaviourObject::removeSubscriber(string id)
{
	m_stateSubsribers.erase(id);
}
void BehaviourObject::notifySubscribers()
{
	for (auto & subsriber : m_stateSubsribers)
		subsriber.second->notify(getState());
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
UniversalModelHandler& BehaviourObject::getModelHandler()
{
	return *m_model.get();
}