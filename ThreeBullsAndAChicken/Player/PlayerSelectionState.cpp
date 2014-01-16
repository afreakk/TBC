#include "stdafx.h"
#include "PlayerSelectionState.h"
#include "../Enemy/EnemyHandler.h"
#include "../OgreCore/OISCore.h"
#include "PlayerStats.h"
PlayerSelectionState::PlayerSelectionState() :PlayerState(PLAYER_STATES::PlayerSelectionState), m_selected(0), m_selectedEntity(nullptr)
{
}


PlayerSelectionState::~PlayerSelectionState()
{
}

void PlayerSelectionState::init()
{
	m_spaceReleased = false;
	getSelectedEntity();
	OISCore::getSingletonPtr()->addKeyListener(this, "PlayerSelectionState");
}
void PlayerSelectionState::exit()
{
	m_hoveredEntity.clear();
	m_selectedEntity = nullptr;
	OISCore::getSingletonPtr()->removeKeyListener("PlayerSelectionState");
}
void PlayerSelectionState::update(PlayerModelHandler& playerModel)
{
	m_playerModelHandler = &playerModel;
	getSelectedEntity();
	m_selectedEntity->setMaterialName("TransparentTexture");
}
void PlayerSelectionState::getSelectedEntity()
{
	EnemyHandler& enemyHandler = EnemyHandler::getSingleton();
	std::vector<Mutant>& enemies = enemyHandler.getMutants();
	m_hoveredModelHandler = &enemies[m_selected].getModelHandler();
	m_selectedEntity = m_hoveredModelHandler->getEntity();
}
bool PlayerSelectionState::keyPressed(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KeyCode::KC_TAB)
	{
		if (m_selectedEntity!= nullptr)
			m_selectedEntity->setMaterialName("red");
		increaseSelected();
	}
	if (e.key == OIS::KeyCode::KC_C&&m_spaceReleased)
		select();
	return true;
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
	if (m_hoveredEntity.size() == 0)
		cost = energyCostOf(m_playerModelHandler->getNormalPos(), m_hoveredModelHandler->getNormalPos());
	else
		cost = energyCostOf(m_hoveredEntity[ m_hoveredEntity.size()-1 ].n, m_hoveredModelHandler->getNormalPos());
	return cost;
}
void PlayerSelectionState::pushbackSelected(const int cost)
{
	for (auto selectedEnemy : m_hoveredEntity)
	{
		if (selectedEnemy.ent == m_selectedEntity)
			return;
	}
	SelectedInfo p;
	p.ent = m_selectedEntity;
	p.n = m_hoveredModelHandler->getNormalPos();
	m_hoveredEntity.push_back(p);
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