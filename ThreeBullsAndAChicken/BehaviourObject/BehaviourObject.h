#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
#include "../BehaviourState/BehaviourStateSubscriber.h"
class BehaviourObject
{
public:
	BehaviourObject(UniversalModelHandler* modelHandler);
	~BehaviourObject();
	void setState(BehaviourState* newState);
	void update();
protected:
	unique_ptr<UniversalModelHandler> m_model;
	BehaviourState* m_currentState;
	std::map <string, BehaviourStateSubscriber*> m_stateSubsribers;
public:
	//subscriberStuff
	void notifySubscribers();
	void addSubsriber(BehaviourStateSubscriber*, string);
	void removeSubscriber(string);
	//gets
	SceneNode* getNode() const ;
	PolarCoordinates getNormalPosition() ;
	UniversalModelHandler& getModelHandler();
	BEHAVOUR_STATE getState() const;
};

