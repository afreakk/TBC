#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "../Enemy/EnemyHandler.h"
#include "../OgreCore/OISCore.h"
#include "PlayerStats.h"
#include "../Enemy/MutantGlobalStats.h"
PlayerSelectionState::PlayerSelectionState() :PlayerState(PLAYER_STATES::PlayerSelectionState), m_selected(0)
, m_hoveredModelHandler(nullptr)
{
}


PlayerSelectionState::~PlayerSelectionState()
{
}

void PlayerSelectionState::init(PlayerModelHandler& modelHandler)
{
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed() / 16.0);
	m_spaceReleased = false;
	getSelectedEntity();
	OISCore::getSingletonPtr()->addKeyListener(this, "PlayerSelectionState");
}
void PlayerSelectionState::exit()
{
	MutantGlobalStats::getSingleton().setWalkSpeed(MutantGlobalStats::getSingleton().getWalkSpeed()*16.0);
	m_hoveredModelHandler = nullptr;
	m_selectedModelHandlers.clear();
	OISCore::getSingletonPtr()->removeKeyListener("PlayerSelectionState");
}
void PlayerSelectionState::update(PlayerModelHandler& playerModel)
{
	m_playerModelHandler = &playerModel;
	getSelectedEntity();
	m_hoveredModelHandler->setMaterial("TransparentTexture");
}
void PlayerSelectionState::getSelectedEntity()
{
	EnemyHandler& enemyHandler = EnemyHandler::getSingleton();
	std::vector<Mutant>& enemies = enemyHandler.getMutants();
	m_hoveredModelHandler = &enemies[m_selected].getModelHandler();
}
bool PlayerSelectionState::keyPressed(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_TAB)
	{
		if (m_hoveredModelHandler!= nullptr)
			m_hoveredModelHandler->setMaterial("red");
		increaseSelected();
	}
	if (e.key == OIS::KeyCode::KC_SPACE&&m_spaceReleased)
		select();
	if (e.key == OIS::KeyCode::KC_RETURN)
		goLERP();
	return true;
}
void PlayerSelectionState::goLERP()
{
	PlayerStats::getSingleton().setAttackList(m_selectedModelHandlers);
	m_nextState = PLAYER_STATES::PlayerLERPState;
}
bool PlayerSelectionState::keyReleased(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_SPACE)
		m_spaceReleased = true;
	return true;
}
void PlayerSelectionState::select()
{
	unsigned cost = costOfSelected();
	unsigned playerEnergy = PlayerStats::getSingleton().getEnergy();
	if (cost <= playerEnergy)
		pushbackSelected(cost);
}
unsigned PlayerSelectionState::costOfSelected()
{
	unsigned cost = 0;
	if (m_selectedModelHandlers.size() == 0)
		cost = energyCostOf(m_playerModelHandler->getNormalPos(), m_hoveredModelHandler->getNormalPos());
	else
		cost = energyCostOf(m_selectedModelHandlers[ m_selectedModelHandlers.size()-1 ]->getNormalPos() , m_hoveredModelHandler->getNormalPos());
	return cost;
}
void PlayerSelectionState::pushbackSelected(const int cost)
{
	for (auto selectedEntity : m_selectedModelHandlers)
	{
		if ( selectedEntity == m_hoveredModelHandler )
			return;
	}
	m_selectedModelHandlers.push_back(m_hoveredModelHandler);
	m_hoveredModelHandler->markAs(m_selectedModelHandlers.size());
	PlayerStats::getSingleton().modifyEnergy(-cost);
}
void PlayerSelectionState::increaseSelected()
{
	EnemyHandler& enemyHandler = EnemyHandler::getSingleton();
	std::vector<Mutant>& enemies = enemyHandler.getMutants();
	if (m_selected < enemies.size()-1)
		m_selected++;
	else
		m_selected = 0;
}