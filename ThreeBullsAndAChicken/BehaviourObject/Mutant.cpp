#include "stdafx.h"
#include "Mutant.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"

Mutant::Mutant(const PolarCoordinates pos) 
: BehaviourObject(new ModelHandlerMutant(pos))
{
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}
