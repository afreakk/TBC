#pragma once
#include "BehaviourStateNormalTranslator.h"
#include "BehaviourState.h"
class BehaviourStateNormal:public BehaviourState
{
public:
	BehaviourStateNormal(const NormalDirection* walkingDirection, const Real* speed);
	void update(ModelHandler& playerModel) override;
	~BehaviourStateNormal();
	bool getSuccess();
private:
	void handleDirection();

	const NormalDirection& m_walkingDirection;
	NormalDirection m_direction;
	BehaviourStateNormalTranslator m_translator;
	bool m_success;

};

