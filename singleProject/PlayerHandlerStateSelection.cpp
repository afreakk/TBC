#include "stdafx.h"
#include "PlayerHandlerStateSelection.h"
#include "MutantContainer.h"
#include "GlobalVariables.h"
#include "PlayerGlobalStats.h"
#include "PlayerSelectionState.h"
#include "BehaviourStateLimbo.h"
#include "Player.h"
#include "ModelHandlerMutant.h"
#include "CoreCompositor.h"

PlayerHandlerStateSelection::PlayerHandlerStateSelection(Player* player)
: m_selectionHandler(m_markedList)
, HandlerState(PLAYER_HANDLER_STATE::SELECTION)
, m_player(player)
, m_selectionState(static_cast<BehaviourState*>(new PlayerSelectionState(&m_player->getModelHandler()) ) )
, m_line(player->getNode(),2.0)
{
	m_player->setState(m_selectionState.get());
	GlobalVariables::getSingleton().setSpeed(PlayerGlobalStats::getSingleton().getSlowMotionPower());
	MutantContainer::getSingleton().registerSubscriber(this,"PlayerHandlerStateSelection");
    CoreCompositor::getSingleton().blackAndWhite(true);
}


PlayerHandlerStateSelection::~PlayerHandlerStateSelection()
{
    CoreCompositor::getSingleton().blackAndWhite(false);
	MutantContainer::getSingleton().removeSubscriber("PlayerHandlerStateSelection");
	GlobalVariables::getSingleton().setSpeed(1.0);
	for (auto& i : m_markedList)
		static_cast<ModelHandlerMutant&>(MutantContainer::getSingleton().getMutant(i)->getModelHandler()).setHovered(selectedType::DEFAULT);
}

void PlayerHandlerStateSelection::update()
{
	m_line.update(boost::numeric_cast<Real>(PlayerGlobalStats::getSingleton().getEnergy()/boost::numeric_cast<Real>(m_selectionHandler.getEnergyCostOfMarked())));
    PlayerGlobalStats::getSingleton().markEnergy( m_selectionHandler.getEnergyCostOfMarked() );
	if (updateMarked())
		newMarked();
}
void PlayerHandlerStateSelection::newMarked()
{
	m_lastSelectedNode = m_selectionHandler.getCurrentMarkedMutant()->getNode();
	m_line.updateBack(m_lastSelectedNode);
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
	{
		m_markedList.erase(w);
		m_line.removeNode(victim);
	}
}
const PolarCoordinates& PlayerHandlerStateSelection::getLatestMarkedPolar(int lookLower)
{
	Mutant * mutant;
	if ((mutant = MutantContainer::getSingleton().getMutant(*(m_markedList.end()-lookLower))) != nullptr)
		return mutant->getPolarCoordinates();
	return getLatestMarkedPolar(lookLower+1);
}
void PlayerHandlerStateSelection::keyPressed(const OIS::KeyEvent& e)
{
	m_selectionHandler.handleKeys(e);
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
	if (m_selectionHandler.getEnergyCostOfMarked() > static_cast<int>(PlayerGlobalStats::getSingleton().getEnergy())
		|| (mutant = MutantContainer::getSingleton().getMutant(marked)) == nullptr)
		return;
    PlayerGlobalStats::getSingleton().markEnergy(0);
	PlayerGlobalStats::getSingleton().modifyEnergy(-static_cast<int>(m_selectionHandler.getEnergyCostOfMarked()));
	static_cast<ModelHandlerMutant&>(mutant->getModelHandler()).setHovered(selectedType::SELECTED);
	m_markedList.push_back(marked);
	m_line.addNode(m_lastSelectedNode);
}

const std::vector<string>& PlayerHandlerStateSelection::getAttackList() const
{
	return m_markedList;
}