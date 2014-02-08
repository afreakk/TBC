#pragma once
#include "stdafx.h"
#include "../BehaviourState/BehaviourState.h"
#include "../Templates/Messager.h"
class BehaviourObject : public Messager<BEHAVOUR_STATE>
{
public:
	BehaviourObject(ModelHandler* modelHandler);
	~BehaviourObject();
	void setState(BehaviourState* newState);
	const BEHAVOUR_STATE message() override
	{
		return  m_currentState->getState();
	}
	void update();
protected:
	unique_ptr<ModelHandler> m_model;
	BehaviourState* m_currentState;
public:
	//gets
	SceneNode* getNode() const ;
	PolarCoordinates getNormalPosition() ;
	ModelHandler& getModelHandler();
	BEHAVOUR_STATE getState() const;
};

