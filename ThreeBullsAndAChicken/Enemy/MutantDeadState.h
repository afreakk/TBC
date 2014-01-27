#pragma once
#include "stdafx.h"
#include "MutantState.h"
class MutantDeadState : public MutantState
{
public:
	MutantDeadState();
	~MutantDeadState();
	void update(MutantModelHandler*)override;
};

