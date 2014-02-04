#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
#include "../Other/MovableText.h"
#include "../UniversalGameObjects/SelectedTag.h"
#include "../UniversalGameObjects/BloodSplat.h"

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
	void damage();
private:
	unique_ptr<MovableText> m_numberText;
	SelectedTag m_selectedTag;
	BloodSplat m_bloodSplat;
	bool m_selected;
	bool m_marked;
};
