#pragma once
#include "ModelHandler.h"
#include "SelectedTag.h"
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
	void fire(bool run=true);
	void init() override;
	WeaponType getWeaponType();
	bool isHovered();
	virtual const Vector3 getBonePos() const ;
	virtual const Vector3 getBoneOrientation()  const ;
private:
	SelectedTag m_selectedTag;
	unique_ptr<WeaponBase> m_weapon;
	WeaponType m_type;
	bool m_hovered;
	bool m_selected;

	void setWeapon(WeaponType weaponType);

};
