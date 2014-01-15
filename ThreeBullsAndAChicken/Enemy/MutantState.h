#pragma once
#include "MutantModelHandler.h"
class MutantState
{
public:
	virtual void update(MutantModelHandler*) = 0;
};

