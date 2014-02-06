#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
#include "../UniversalGameObjects/SelectedTag.h"
#include "../UniversalGameObjects/BloodSplat.h"
#include "../UniversalGameObjects/MutantFlameThrower.h"
#include "../UniversalGameObjects/MutantNumber.h"

class ModelHandlerMutant : public ModelHandler
{
public:
	ModelHandlerMutant(PolarCoordinates normalPos);
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
	SelectedTag m_selectedTag;
	BloodSplat m_bloodSplat;
	MutantFlameThrower m_flameThrower;
	MutantNumber m_number;
	bool m_hovered;
};
