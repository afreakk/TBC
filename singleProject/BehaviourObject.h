#pragma once
#include "Messager.h"
#include "PolarCoordinates.h"
#include "BehaviourState.h"
#include <memory>
class BehaviourState;
class ModelHandler;
enum class BObjectType
{
    Player,
    Mutant
};
class BehaviourObject : public Messager<BEHAVOUR_STATE>
{
public:
	BehaviourObject(ModelHandler* modelHandler, BObjectType type);
	~BehaviourObject();
	void setState(BehaviourState* newState);
	const BEHAVOUR_STATE message() override
	{
		return  m_currentState->getState();
	}
	void update();
protected:
	std::unique_ptr<ModelHandler> m_model;
	const BObjectType m_objectType;
	BehaviourState* m_currentState;
	Ogre::Real m_selectionPhaseThetaOffset;
	bool m_dead;
public:
	//gets
	BObjectType getObjectType() const;
	Ogre::SceneNode* getNode() const ;
	const PolarCoordinates& getPolarCoordinates() const;
	const Ogre::Real getSelectionTheta() const;
	void setSelectionThetaOffset(const Ogre::Real& offset);
	ModelHandler& getModelHandler();
	const ModelHandler& getModelHandler() const;
	BEHAVOUR_STATE getState() const;
	void setDead(const bool valu);
	bool isDead() const;
};

