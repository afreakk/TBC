#pragma once
#include "HandlerState.h"
#include "MutantHandlerEnums.h"
class BehaviourStateLERP;
class BehaviourObject;
class MutantHandlerStateSuicideBomb : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateSuicideBomb(BehaviourObject* mutant, BehaviourObject* playerObject);
	~MutantHandlerStateSuicideBomb();
	void update() override;
private:
	BehaviourObject* m_mutant;
	unique_ptr<BehaviourStateLERP> m_mutState;
	Ogre::Real m_detonationTimer;
	bool m_activated;
};
