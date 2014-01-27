#pragma once
#include "GameState.h"
#include "../Enemy/Mutant.h"
#include "GameStateSelectionHandler.h"
class GameStateSelection : public GameState
{
public:
	GameStateSelection();
	~GameStateSelection();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
	std::vector<unsigned> getAttackList() const;
private:
	std::vector<unsigned> m_attackList;
	GameStateSelectionHandler m_selectionHandler;
	void handleSelection(const OIS::KeyEvent&);
	void pushBackSelected();
	void goLerp();

};

