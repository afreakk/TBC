#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "ModelRecipeMutant.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"
#include "WeaponTypes.h"

using namespace Ogre;
ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos, WeaponType weaponType)
: ModelHandler(new ModelRecipeMutant(), normalPos)
, m_selectedTag(m_node)
, m_bloodSplat(m_node, this)
, m_weapon( nullptr)
, m_number(m_node)
, m_hovered(false)
{
	setWeapon(weaponType);
	setHovered(false);
}
ModelHandlerMutant::~ModelHandlerMutant()
{
	cout << "ModelHandlerMutant destrucotr" << endl;
}
void ModelHandlerMutant::init()
{
	ModelHandler::init();
}

void ModelHandlerMutant::damage(Vector3 direction)
{
	m_bloodSplat.setDirection(direction);
	m_bloodSplat.activate();
}
void ModelHandlerMutant::fire()
{
	m_weapon->activate();
}
void ModelHandlerMutant::setHovered(bool selected)
{
	m_hovered = selected;
	if (m_hovered)
		m_selectedTag.select();
}
void ModelHandlerMutant::setWeapon(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType::LAZER:
		m_weapon = unique_ptr<WeaponBase>(new MutantLazer(m_node, this));
		break;
	case WeaponType::FLAMETHROWER:
		m_weapon = unique_ptr<WeaponBase>(new MutantFlameThrower(m_node, this));
		break;
	case WeaponType::FIREBALL:
		m_weapon = unique_ptr<WeaponBase>(new MutantFireBall(m_node, this));
		break;
	default:
		assert(0);
		break;
	}
}