#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
#include "../Other/MovableText.h"
#include "../UniversalGameObjects/SelectedTag.h"
#include "../UniversalGameObjects/BloodSplat.h"
#include "../UniversalGameObjects/MutantFlameThrower.h"

class ModelHandlerMutant : public ModelHandler
{
public:
	ModelHandlerMutant(PolarCoordinates normalPos);
	~ModelHandlerMutant();
	void markAs(int number);
	void unMarkNumber();
	void markSelected(bool);
	bool isSelected() const
	{
		return m_selected;
	}
	void fire();
	void damage(Vector3 direction);
private:
	SelectedTag m_selectedTag;
	BloodSplat m_bloodSplat;
	MutantFlameThrower m_flameThrower;
	bool m_selected;
	bool m_marked;
	unique_ptr<MovableText> m_numberText;
};
