#include "stdafx.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "../Enemy/EnemyHandler.h"
#include "../Enemy/MutantModelHandler.h"
PlayerHandlerStateSelectionHandler::PlayerHandlerStateSelectionHandler()
: m_mutants(EnemyHandler::getSingleton().getMutants() )
, m_selectedIndex(0)
, m_lastSelectedIndex(m_selectedIndex)
{
}


PlayerHandlerStateSelectionHandler::~PlayerHandlerStateSelectionHandler()
{
}

void PlayerHandlerStateSelectionHandler::updateSelected()
{
	MutantModelHandler& lastSelectedModelHandler = static_cast<MutantModelHandler&>(m_mutants[m_lastSelectedIndex]->getModelHandler());
	if (m_lastSelectedIndex != m_selectedIndex)
		static_cast<MutantModelHandler&>(m_mutants[m_lastSelectedIndex]->getModelHandler()).markSelected(false);
	static_cast<MutantModelHandler&>(m_mutants[m_selectedIndex]->getModelHandler()).markSelected(true);
	m_lastSelectedIndex = m_selectedIndex;
}
void PlayerHandlerStateSelectionHandler::handleIndex(const OIS::KeyEvent& e)
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
void PlayerHandlerStateSelectionHandler::changeIndex(int iVel)
{
	m_selectedIndex += iVel;
	if (m_selectedIndex > m_mutants.size() - 1)
		m_selectedIndex -= iVel;
	else if (m_selectedIndex < 0)
		m_selectedIndex -= iVel;
}
void PlayerHandlerStateSelectionHandler::extremeChangeIndex(int iVel)
{
	if (iVel>0)
		m_selectedIndex = m_mutants.size() - 1;
	else
		m_selectedIndex = 0;
}
unsigned PlayerHandlerStateSelectionHandler::getSelected() const
{
	return m_selectedIndex;
}