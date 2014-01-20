#pragma once
#include "stdafx.h"
#include "MutantState.h"
class MutantLERPState : public MutantState
{
public:
	MutantLERPState();
	~MutantLERPState();
	void update(MutantModelHandler*) override;
	void init(MutantModelHandler*) override;
	void exit() override;
private:
	LERP_STATE m_lerpState;
};

