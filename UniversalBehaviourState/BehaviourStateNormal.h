#pragma once
#include "stdafx.h"
#include "BehaviourStateNormalTranslator.h"
#include "../UniversalBehaviourState/BehaviourState.h"
class BehaviourStateNormal:public BehaviourState
{
public:
	BehaviourStateNormal(const NormalDirection* walkingDirection, const Real* speed);
	void update(UniversalModelHandler& playerModel) override;
	~BehaviourStateNormal();
private:
	void handleDirection();

	const NormalDirection& m_walkingDirection;
	NormalDirection m_direction;
	BehaviourStateNormalTranslator m_translator;

};

