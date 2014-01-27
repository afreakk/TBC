#include "stdafx.h"
#include "GameStateSelection.h"
#include "../Enemy/MutantGlobalStats.h"
#include "../Enemy/EnemyHandler.h"
GameStateSelection::GameStateSelection() :GameState(PLAYER_STATES::PlayerSelectionState)
{
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed() / 16.0);
}


GameStateSelection::~GameStateSelection()
{
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed()*16.0);
}

void GameStateSelection::update()
{
	m_selectionHandler.updateSelected();
}
void GameStateSelection::keyPressed(const OIS::KeyEvent& e)
{
	m_selectionHandler.handleIndex(e);
	handleSelection(e);
}
void GameStateSelection::keyReleased(const OIS::KeyEvent& e)
{

}
void GameStateSelection::handleSelection(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_SPACE)
		pushBackSelected();
	if (e.key == OIS::KC_RETURN && m_attackList.size()>0)
		goLerp();
}
std::vector<unsigned> GameStateSelection::getAttackList() const
{
	return m_attackList;
}
void GameStateSelection::goLerp()
{
	m_state = PLAYER_STATES::PlayerLERPState;
}
void GameStateSelection::pushBackSelected()
{
	m_attackList.push_back(m_selectionHandler.getSelected());
	EnemyHandler::getSingleton().getMutantHandlers()[m_attackList[m_attackList.size() - 1]]->getMutant().getModelHandler().markAs(m_attackList.size());
}
