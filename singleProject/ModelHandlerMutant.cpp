#include "stdafx.h"
#include "ModelHandlerMutant.h"

#include "ModelRecipeMutant.h"
#include "GlobalVariables.h"
#include "MutantGlobalStats.h"
#include "WeaponTypes.h"

ModelHandlerMutant::ModelHandlerMutant(PolarCoordinates normalPos, WeaponType weaponType, ModelRecipe* modlRecipe)
: ModelHandler(modlRecipe, normalPos,ModelHandlerType::Mutant)
, m_selectedTag(m_node)
, m_bloodSplat(m_node, this)
, m_weapon( nullptr)
, m_type(WeaponType::NOTHING)
, m_hovered(false)
, m_selected(false)
{
	setWeapon(weaponType);
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
bool ModelHandlerMutant::isHovered()
{
	return m_hovered;
}
void ModelHandlerMutant::setHovered(selectedType type)
{
	switch (type)
	{
	case selectedType::HOVERED:
		m_entity->setMaterialName("HoveredMaterial");
        m_selectedTag.select();
		m_hovered = true;
		break;
	case selectedType::SELECTED:
		m_entity->setMaterialName("SelectedMaterial");
		m_selected = true;
		break;
	case selectedType::DEFAULT:
		m_entity->setMaterialName(m_crRecipe->getMaterialName());
		m_selected = false;
		m_hovered = false;
		break;
	case selectedType::UNHOVERED:
		if (!m_selected)
		    m_entity->setMaterialName(m_crRecipe->getMaterialName());
		m_hovered = false;
		break;
	default:
		break;
	}
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