#pragma once
#include "stdafx.h"
#include "PlayerState.h"
#include "PlayerModelHandler.h"
#include "../Enemy/MutantModelHandler.h"
struct SelectedInfo
{
	Entity* ent;
	NormalPosition n;
};
class PlayerSelectionState:public PlayerState, public OIS::KeyListener
{
public:
	PlayerSelectionState();
	~PlayerSelectionState();
	void init() override;
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

	bool m_spaceReleased;
	unsigned m_energyCost;
	unsigned m_selected;
	Entity* m_selectedEntity;
	std::vector<SelectedInfo> m_hoveredEntity;
	MutantModelHandler* m_hoveredModelHandler;
	PlayerModelHandler* m_playerModelHandler;
};

