#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerModelHandler.h"
#include "../Enemy/MutantModelHandler.h"

class PlayerSelectionState:public PlayerState, public OIS::KeyListener
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void init(PlayerModelHandler& modelHandler) override;
	void exit() override;
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
	void update(PlayerModelHandler& playerModel) override;
private:
	void increaseSelected();
	void getSelectedEntity();
	void pushbackSelected(const int cost);
	unsigned costOfSelected();
	void select();
	void goLERP();

	bool m_spaceReleased;
	unsigned m_energyCost;
	unsigned m_selected;
	std::vector<MutantModelHandler*> m_selectedModelHandlers;
	MutantModelHandler* m_hoveredModelHandler;
	PlayerModelHandler* m_playerModelHandler;
};

