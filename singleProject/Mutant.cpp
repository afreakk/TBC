#include "stdafx.h"
#include "Mutant.h"
#include "ModelHandlerMutant.h"

Mutant::Mutant(const PolarCoordinates pos, WeaponType weaponType) 
: BehaviourObject(new ModelHandlerMutant(pos, weaponType))
{
	m_model->init();
}


Mutant::~Mutant()
{
	cout << "mutant destrocutor" << endl;
}
