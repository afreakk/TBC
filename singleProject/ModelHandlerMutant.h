#pragma once
#include "UnitCircleMovement.h"
#include "ModelHandler.h"
#include "SelectedTag.h"
#include "BloodSplat.h"
#include "MutantFlameThrower.h"
#include "MutantNumber.h"

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
