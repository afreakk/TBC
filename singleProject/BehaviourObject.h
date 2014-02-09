#pragma once
#include "Messager.h"
#include "PolarCoordinates.h"
#include "BehaviourState.h"
#include <memory>
class BehaviourState;
class ModelHandler;
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
	std::unique_ptr<ModelHandler> m_model;
	BehaviourState* m_currentState;
public:
	//gets
	Ogre::SceneNode* getNode() const ;
	PolarCoordinates getNormalPosition() ;
	ModelHandler& getModelHandler();
	BEHAVOUR_STATE getState() const;
};

