#pragma once
#include "stdafx.h"
class PlayerGUIStyle
{
public:
	PlayerGUIStyle();
	~PlayerGUIStyle();
	void setEnergy(int);
private:
	void loadFont();
	void setupEnergyGUI();
	Real m_energyMaxWidth;
	Real m_energyHeight;
	OverlayContainer* m_energyBar;
	TextAreaOverlayElement* m_energyText;
	Overlay* m_overlay;
};

