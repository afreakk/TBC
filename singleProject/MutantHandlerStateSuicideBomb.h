#pragma once
#include "HandlerState.h"
#include "MutantHandlerEnums.h"
class Mutant;
class BehaviourStateLERP;
class MutantHandlerStateSuicideBomb : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateSuicideBomb(Mutant* mutant, SceneNode* playerNode);
	~MutantHandlerStateSuicideBomb();
	void update() override;
private:
	Mutant* m_mutant;
	unique_ptr<BehaviourStateLERP> m_mutState;
	Ogre::Real m_detonationTimer;
	bool m_activated;
};
