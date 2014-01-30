#pragma once
#include "stdafx.h"
#include "../Templates/HandlerState.h"
#include "../BehaviourObject/Mutant.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "../BehaviourState/PlayerSelectionState.h"
#include "../BehaviourObject/Player.h"
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

