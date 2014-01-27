#pragma once
#include "../Enemy/EnemyHandler.h"
class GameStateSelectionHandler
{
public:
	GameStateSelectionHandler();
	~GameStateSelectionHandler();
	void handleIndex(const OIS::KeyEvent&);
	void changeIndex(int iVel);
	void extremeChangeIndex(int iVel);
	void updateSelected();
	unsigned getSelected()const ;
private:
	std::vector<unique_ptr<MutantHandler>>&  m_mutants;
	unsigned m_selectedIndex;
	unsigned m_lastSelectedIndex;
};

