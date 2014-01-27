#include "stdafx.h"
#include "GameStateSelectionHandler.h"
#include "../Enemy/EnemyHandler.h"

GameStateSelectionHandler::GameStateSelectionHandler(): m_mutants(EnemyHandler::getSingleton().getMutantHandlers() ), m_selectedIndex(0)
, m_lastSelectedIndex(m_selectedIndex)
{
}


GameStateSelectionHandler::~GameStateSelectionHandler()
{
}

void GameStateSelectionHandler::updateSelected()
{
	if (m_lastSelectedIndex != m_selectedIndex)
		m_mutants[m_lastSelectedIndex]->getMutant().getModelHandler().markSelected(false);
	m_mutants[m_selectedIndex]->getMutant().getModelHandler().markSelected(true);
	m_lastSelectedIndex = m_selectedIndex;
}
void GameStateSelectionHandler::handleIndex(const OIS::KeyEvent& e)
{
	int idxVelocity = 0;
	if (e.key == OIS::KC_A)
		idxVelocity++;
	if (e.key == OIS::KC_D)
		idxVelocity--;
	if (idxVelocity != 0)
		changeIndex(idxVelocity);

	int goTo = 0;
	if (e.key == OIS::KC_W)
		goTo++;
	if (e.key == OIS::KC_S)
		goTo--;
	if (goTo != 0)
		extremeChangeIndex(goTo);
}
void GameStateSelectionHandler::changeIndex(int iVel)
{
	m_selectedIndex += iVel;
	if (m_selectedIndex > m_mutants.size() - 1)
		m_selectedIndex -= iVel;
	else if (m_selectedIndex < 0)
		m_selectedIndex -= iVel;
}
void GameStateSelectionHandler::extremeChangeIndex(int iVel)
{
	if (iVel>0)
		m_selectedIndex = m_mutants.size() - 1;
	else
		m_selectedIndex = 0;
}
unsigned GameStateSelectionHandler::getSelected() const
{
	return m_selectedIndex;
}