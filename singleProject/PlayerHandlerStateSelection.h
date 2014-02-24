#pragma once
#include "HandlerState.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "PlayerHandlerEnums.h"
#include "MessageSubscriber.h"
#include "PlayerHandlerStateSelectionLine.h"
class Player;
class PlayerSelectionState;
class BehaviourState;
class PlayerHandlerStateSelection : public HandlerState <PLAYER_HANDLER_STATE>, public MessageSubscriber<std::string>
{
public:
	PlayerHandlerStateSelection(Player* player);
	~PlayerHandlerStateSelection();
	void update() override;
	void keyPressed(const OIS::KeyEvent&) override;
	void keyReleased(const OIS::KeyEvent&) override;

	const std::vector<string>& getAttackList() const;
	void notify(std::string) override;
private:
	PlayerHandlerStateSelectionHandler m_selectionHandler;
	Player* m_player;
	unique_ptr<BehaviourState> m_selectionState;
	std::vector<std::string> m_markedList;
	PlayerHandlerStateSelectionLine m_selectionLine;

	void newMarked();
	void handleSelection(const OIS::KeyEvent&);
	const PolarCoordinates& getLatestMarkedPolar(int lookLower=1);
	void selectMarked();
	bool updateMarked();
	void markEnergy();
};

