#pragma once
#include "ModelHandler.h"
#include "SelectedTag.h"
#include "BloodSplat.h"
#include "MutantNumber.h"
#include "Weapon.h"
class ModelHandlerMutant : public ModelHandler
{
public:
	ModelHandlerMutant(PolarCoordinates normalPos,  WeaponType weaponType);
	~ModelHandlerMutant();
	void setHovered(bool);
	bool isHovered() const
	{
		return m_hovered;
	}
	void fire();
	void damage(Vector3 direction);
	MutantNumber& getNumer()
	{
		return m_number;
	}
private:
	void setWeapon(WeaponType weaponType);

	SelectedTag m_selectedTag;
	BloodSplat m_bloodSplat;
	unique_ptr<WeaponBase> m_weapon;
	MutantNumber m_number;
	bool m_hovered;
};
