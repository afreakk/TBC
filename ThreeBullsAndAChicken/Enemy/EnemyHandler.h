#pragma once
#include "Mutant.h"
#include <vector>
class EnemyHandler
{
public:
	EnemyHandler();
	~EnemyHandler();
	void update();
private:
	std::vector<Mutant> mutants;

};

