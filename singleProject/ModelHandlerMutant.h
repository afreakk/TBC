#pragma once
#include "ModelHandler.h"
#include "SelectedTag.h"
#include "BloodSplat.h"
#include "Weapon.h"
enum class selectedType
{
    HOVERED,
    SELECTED,
    DEFAULT,
    UNHOVERED

};
class ModelHandlerMutant : public ModelHandler
{
public:
	ModelHandlerMutant(PolarCoordinates normalPos,  WeaponType weaponType, ModelRecipe* modlRecipe);
	~ModelHandlerMutant();
	void setHovered(selectedType);
	void fire();
	void init() override;
	void damage(Vector3 direction);
	WeaponType getWeaponType();
	bool isHovered();
private:
	SelectedTag m_selectedTag;
	BloodSplat m_bloodSplat;
	unique_ptr<WeaponBase> m_weapon;
	WeaponType m_type;
	bool m_hovered;
	bool m_selected;

	void setWeapon(WeaponType weaponType);

};
