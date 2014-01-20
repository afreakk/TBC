#pragma once
#include "stdafx.h"
#include "MutantState.h"
class MutantNormalState:public MutantState
{
public:
	MutantNormalState();
	~MutantNormalState();
	void update(MutantModelHandler* )override;
	void init(MutantModelHandler*)override;
	void exit()override;
private:
};

