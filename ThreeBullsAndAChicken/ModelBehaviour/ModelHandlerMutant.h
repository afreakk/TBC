#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/ModelHandler.h"
#include "../Other/MovableText.h"
#include "../UniversalGameObjects/SelectedTag.h"

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
private:
	unique_ptr<MovableText> m_numberText;
	SelectedTag m_selectedTag;
	bool m_selected;
	bool m_marked;
};
