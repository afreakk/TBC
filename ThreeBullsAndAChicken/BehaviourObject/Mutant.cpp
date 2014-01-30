#include "stdafx.h"
#include "Mutant.h"
#include "../ModelBehaviour/MutantModelHandler.h"

Mutant::Mutant(const PolarCoordinates pos) 
: BehaviourObject(new MutantModelHandler(pos))
{
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}
