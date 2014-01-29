#include "stdafx.h"
#include "PlayerHandlerStateSelection.h"
#include "../Enemy/MutantGlobalStats.h"
#include "../Enemy/MutantModelHandler.h"
#include "../Containers/MutantContainer.h"
PlayerHandlerStateSelection::PlayerHandlerStateSelection(Player* player) 
:HandlerState(PLAYER_HANDLER_STATE::SELECTION)
, m_player(player)
, m_selectionState{ new PlayerSelectionState() }

{
	m_player->setState(m_selectionState.get());
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed() / 16.0);
}


PlayerHandlerStateSelection::~PlayerHandlerStateSelection()
{
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed()*16.0);
}

void PlayerHandlerStateSelection::update()
{
	m_selectionHandler.updateSelected();
}
void PlayerHandlerStateSelection::keyPressed(const OIS::KeyEvent& e)
{
	m_selectionHandler.handleIndex(e);
	handleSelection(e);
}
void PlayerHandlerStateSelection::keyReleased(const OIS::KeyEvent& e)
{

}
void PlayerHandlerStateSelection::handleSelection(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_SPACE)
		pushBackSelected();
	if (e.key == OIS::KC_RETURN && m_attackList.size()>0)
		goLerp();
}
std::vector<unsigned> PlayerHandlerStateSelection::getAttackList() const
{
	return m_attackList;
}
void PlayerHandlerStateSelection::goLerp()
{
	m_state = PLAYER_HANDLER_STATE::LERP;
}
void PlayerHandlerStateSelection::pushBackSelected()
{
	m_attackList.push_back(m_selectionHandler.getSelected());
	static_cast<MutantModelHandler&>(MutantContainer::getSingleton().getMutants()[m_attackList[m_attackList.size() - 1]]->getModelHandler()).markAs(m_attackList.size());
}
