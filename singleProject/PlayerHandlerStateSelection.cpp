#include "stdafx.h"
#include "PlayerHandlerStateSelection.h"
#include "MutantContainer.h"
#include "GlobalVariables.h"
#include "PlayerGlobalStats.h"
#include "PlayerSelectionState.h"
#include "BehaviourStateLimbo.h"
#include "Player.h"
#include "ModelHandlerMutant.h"

PlayerHandlerStateSelection::PlayerHandlerStateSelection(Player* player)
: m_selectionHandler(player->getNode()->getPosition(), m_attackList)
, HandlerState(PLAYER_HANDLER_STATE::SELECTION)
, m_player(player)
, m_selectionState(MutantContainer::getSingleton().getMutants().size() > 0 ? static_cast<BehaviourState*>(new PlayerSelectionState()) : static_cast<BehaviourState*>(new BehaviourStateLimbo()))
{
	if (! (MutantContainer::getSingleton().getMutants().size()>0))
        m_state = PLAYER_HANDLER_STATE::NORMAL;
	m_player->setState(m_selectionState.get());
	GlobalVariables::getSingleton().setSpeed(1.0 / 20.0);
}


PlayerHandlerStateSelection::~PlayerHandlerStateSelection()
{
	GlobalVariables::getSingleton().setSpeed(1.0);
	for (auto idx:m_attackList)
		static_cast<ModelHandlerMutant&>(MutantContainer::getSingleton().getMutants()[idx]->getModelHandler()).getNumer().unMarkNumber();
}

void PlayerHandlerStateSelection::update()
{
	auto siz = MutantContainer::getSingleton().getMutants().size();
	if (! (siz>0))
        m_state = PLAYER_HANDLER_STATE::NORMAL;
	if (m_state != m_originalState)
		return;
	updateMarked();
	markEnergy();
}
void PlayerHandlerStateSelection::markEnergy()
{
	if (currentMarkedIsInList())
	    PlayerGlobalStats::getSingleton().markEnergy( 0);
	else
	    PlayerGlobalStats::getSingleton().markEnergy( m_selectionHandler.getEnergyCostOfMarked() );
}
void PlayerHandlerStateSelection::updateMarked()
{
	if (m_attackList.size() > 0)
		m_selectionHandler.updateMarked(MutantContainer::getSingleton().getMutants()[m_attackList.back()]->getPolarCoordinates());
	else
		m_selectionHandler.updateMarked(m_player->getPolarCoordinates());
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
	if (e.key == OIS::KC_Q)
		m_state = PLAYER_HANDLER_STATE::NORMAL;
	else if (e.key == OIS::KC_RETURN && m_attackList.size()>0)
        m_state = PLAYER_HANDLER_STATE::MULTI_ATTACK;
}
void PlayerHandlerStateSelection::pushBackSelected()
{
	if (currentMarkedIsInList())
		return;
	if (m_selectionHandler.getEnergyCostOfMarked() > PlayerGlobalStats::getSingleton().getEnergy())
		return;
	PlayerGlobalStats::getSingleton().modifyEnergy(-static_cast<int>(m_selectionHandler.getEnergyCostOfMarked()));
	m_attackList.push_back(m_selectionHandler.getMarked());
	static_cast<ModelHandlerMutant&>(MutantContainer::getSingleton().getMutants()[m_attackList[m_attackList.size() - 1]]->getModelHandler()).getNumer().markAs(m_attackList.size());
	m_selectionHandler.addLine();
}

bool PlayerHandlerStateSelection::currentMarkedIsInList()
{
	for (const auto& atk : m_attackList)
	{
		if (m_selectionHandler.getMarked() == atk)
			return true;
	}
	return false;
}
std::vector<unsigned> PlayerHandlerStateSelection::getAttackList() const
{
	return m_attackList;
}