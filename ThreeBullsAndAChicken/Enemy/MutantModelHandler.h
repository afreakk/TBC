#pragma once
#include "stdafx.h"
#include "../Other/UnitCircleMovement.h"
#include "../UniversalGameObjects/UniversalModelHandler.h"
#include "../Other/MovableText.h"

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
	bool m_selected;
	bool m_marked;
};
