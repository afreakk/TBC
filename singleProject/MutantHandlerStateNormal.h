#pragma once
#include "HandlerState.h"
#include "ENUMNormalDirection.h"
#include "MutantHandlerEnums.h"
#include "PolarCoordinates.h"
class Mutant;
class BehaviourStateNormal;
class MutantHandlerStateNormal : public HandlerState <MUTANT_HANDLER_STATE>
{
public:
	MutantHandlerStateNormal(Mutant* mutant, const PolarCoordinates& plarerCoords);
	~MutantHandlerStateNormal();
	void update() override;
private:
	Mutant* m_mutant;
	const PolarCoordinates& m_playerCoords;
	NormalDirection m_walkingDirection;
	unique_ptr<BehaviourStateNormal> m_normalState;

	void goAttack();
	void steerTowardsPlayer();
};

