#pragma once
#include "stdafx.h"
#include "MutantState.h"
#include "MutantModelHandler.h"
class Mutant  : public boost::noncopyable
{
public:
	Mutant(const PolarCoordinates pos, Ogre::SceneNode* playerNode);
	~Mutant();
	void update();
	void setState(MUTANT_STATES);
	const MutantModelHandler& getModelHandler() const;
	MutantModelHandler& getModelHandler();
	string getMaterialName()const;
	const MutantState* getCurrentState()
	{
		return m_currentState.get();
	}
private:
	MutantModelHandler m_modelHolder;
	unique_ptr<MutantState> m_currentState;
	Ogre::SceneNode* m_playerNode;
};

