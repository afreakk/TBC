#include "stdafx.h"
#include "EnemyHandler.h"


EnemyHandler::EnemyHandler() 
{
	mutants.push_back(Mutant());
}


void EnemyHandler::update()
{
	for (auto& mutant : mutants)
		mutant.update();
}
EnemyHandler::~EnemyHandler()
{
}
