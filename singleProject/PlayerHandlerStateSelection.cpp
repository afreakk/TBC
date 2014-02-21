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
: m_selectionHandler(m_markedList)
, HandlerState(PLAYER_HANDLER_STATE::SELECTION)
, m_player(player)
, m_selectionState(static_cast<BehaviourState*>(new PlayerSelectionState() ) )
{
	m_player->setState(m_selectionState.get());
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
	MutantContainer::getSingleton().registerSubscriber(this,"PlayerHandlerStateSelection");
}


PlayerHandlerStateSelection::~PlayerHandlerStateSelection()
{
	MutantContainer::getSingleton().removeSubscriber("PlayerHandlerStateSelection");
	GlobalVariables::getSingleton().setSpeed(1.0);
	for (auto idx : m_markedList)
	{
		Mutant* mutant;
		if((mutant = MutantContainer::getSingleton().getMutant(idx)) != nullptr)
		    static_cast<ModelHandlerMutant&>(mutant->getModelHandler()).getNumer().unMarkNumber();
	}
}

void PlayerHandlerStateSelection::update()
{
	if(updateMarked())
	    markEnergy();
}
void PlayerHandlerStateSelection::markEnergy()
{
    PlayerGlobalStats::getSingleton().markEnergy( m_selectionHandler.getEnergyCostOfMarked() );
}
bool PlayerHandlerStateSelection::updateMarked()
{
	if (m_markedList.size() > 0)
		return m_selectionHandler.updateMarked(getLatestMarkedPolar());
	else
		return m_selectionHandler.updateMarked(m_player->getPolarCoordinates());
}
void PlayerHandlerStateSelection::notify(std::string victim)
{
	auto w = m_markedList.end();
	if ((w = std::find(m_markedList.begin(), m_markedList.end(), victim)) != m_markedList.end())
		m_markedList.erase(w);
}
const PolarCoordinates& PlayerHandlerStateSelection::getLatestMarkedPolar(int lookLower)
{
	Mutant * mutant;
	if ((mutant = MutantContainer::getSingleton().getMutant(*(m_markedList.end()-lookLower))) != nullptr)
		return mutant->getPolarCoordinates();
	getLatestMarkedPolar(lookLower+1);
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
	if (e.key == OIS::KC_SPACE || e.key == OIS::KC_C)
		selectMarked();
	if (e.key == OIS::KC_Q)
		m_state = PLAYER_HANDLER_STATE::NORMAL;
	else if (e.key == OIS::KC_RETURN && m_markedList.size()>0)
        m_state = PLAYER_HANDLER_STATE::MULTI_ATTACK;
}
void PlayerHandlerStateSelection::selectMarked()
{
	const std::string& marked = m_selectionHandler.getMarked();
	if (marked == "NONE")
		return;
	Mutant* mutant;
	if (m_selectionHandler.getEnergyCostOfMarked() > PlayerGlobalStats::getSingleton().getEnergy() 
		|| (mutant = MutantContainer::getSingleton().getMutant(marked)) == nullptr)
		return;
	PlayerGlobalStats::getSingleton().modifyEnergy(-static_cast<int>(m_selectionHandler.getEnergyCostOfMarked()));
	m_markedList.push_back(marked);
	static_cast<ModelHandlerMutant&>(mutant->getModelHandler()).getNumer().markAs(m_markedList.size());
	m_selectionHandler.addLine();
}

const std::vector<string>& PlayerHandlerStateSelection::getAttackList() const
{
	return m_markedList;
}