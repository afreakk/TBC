#include "stdafx.h"
#include "Mutant.h"
#include "../ModelBehaviour/ModelHandlerMutant.h"

Mutant::Mutant(const PolarCoordinates pos) 
: BehaviourObject(new ModelHandlerMutant(pos))
{
	m_model->init();
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}
