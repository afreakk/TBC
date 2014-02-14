#pragma once
#include "HandlerState.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "PlayerHandlerEnums.h"
class Player;
class PlayerSelectionState;
class BehaviourState;
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
	unique_ptr<BehaviourState> m_selectionState;
	std::vector<unsigned> m_attackList;

	void handleSelection(const OIS::KeyEvent&);
	void pushBackSelected();
	bool currentMarkedIsInList();
	void updateMarked();
	void markEnergy();

};

