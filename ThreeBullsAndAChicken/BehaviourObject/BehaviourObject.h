#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
#include "../Templates/Messager.h"
class BehaviourObject : public Messager<BEHAVOUR_STATE>
{
public:
	BehaviourObject(UniversalModelHandler* modelHandler);
	~BehaviourObject();
	void setState(BehaviourState* newState);
	const BEHAVOUR_STATE& message() override
	{
		return  m_currentState->getState();
	}
	void update();
protected:
	unique_ptr<UniversalModelHandler> m_model;
	BehaviourState* m_currentState;
public:
	//gets
	SceneNode* getNode() const ;
	PolarCoordinates getNormalPosition() ;
	UniversalModelHandler& getModelHandler();
	BEHAVOUR_STATE getState() const;
};

