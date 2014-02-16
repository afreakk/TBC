#include "stdafx.h"
#include "Mutant.h"
#include "ModelHandlerMutant.h"
#include "ModelRecipe.h"

Mutant::Mutant(const PolarCoordinates pos, WeaponType weaponType, ModelRecipe* modelRecipe) 
: BehaviourObject(new ModelHandlerMutant(pos,weaponType, modelRecipe))
{
	m_model->init();
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}
