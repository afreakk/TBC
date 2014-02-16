#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "ModelRecipeMutant.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"
#include "WeaponTypes.h"

ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos, WeaponType weaponType, ModelRecipe* modlRecipe)
: ModelHandler(modlRecipe, normalPos)
, m_selectedTag(m_node)
, m_bloodSplat(m_node, this)
, m_weapon( nullptr)
, m_number(m_node)
, m_hovered(false)
, m_type(WeaponType::NOTHING)
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
	m_type = weaponType;
	switch (m_type)
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
	case WeaponType::SUICIDE_BOMB:
		m_weapon = unique_ptr<WeaponBase>(new MutantSuicide(m_node, this));
		break;
	default:
		assert(0);
		break;
	}
}
WeaponType ModelHandlerMutant::getWeaponType()
{
	return m_type;
}