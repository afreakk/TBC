#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../ModelBehaviour/UniversalModelHandler.h"
#include "../Other/MovableText.h"
#include "../UniversalGameObjects/SelectedTag.h"

class MutantModelHandler : public UniversalModelHandler
{
public:
	MutantModelHandler(PolarCoordinates normalPos);
	~MutantModelHandler();
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
