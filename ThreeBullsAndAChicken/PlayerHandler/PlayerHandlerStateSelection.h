#pragma once
#include "../UniversalGameObjects/HandlerState.h"
#include "../Enemy/Mutant.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "../Player/PlayerSelectionState.h"
class PlayerHandlerStateSelection : public HandlerState <PLAYER_HANDLER_STATE>
{
public:
	PlayerHandlerStateSelection(Player* player);
	~PlayerHandlerStateSelection();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;
	std::vector<unsigned> getAttackList() const;
private:
	PlayerHandlerStateSelectionHandler m_selectionHandler;
	Player* m_player;
	unique_ptr<PlayerSelectionState> m_selectionState;
	std::vector<unsigned> m_attackList;

	void handleSelection(const OIS::KeyEvent&);
	void pushBackSelected();
	void goLerp();

};

