#include "stdafx.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "ModelHandlerMutant.h"
#include "MutantContainer.h"
PlayerHandlerStateSelectionHandler::PlayerHandlerStateSelectionHandler(Vector3 playerPos, const std::vector<unsigned>& attackList)
: m_mutants(MutantContainer::getSingleton().getAndSortMutants(playerPos) )
, m_markedIndex(0)
, m_energyCostOfCurrentlyMarked(0)
, m_lastMarkedIndex(m_markedIndex)
, m_attackListConst(attackList)
{
}


PlayerHandlerStateSelectionHandler::~PlayerHandlerStateSelectionHandler()
{
}

void PlayerHandlerStateSelectionHandler::updateMarked(PolarCoordinates currentNode)
{
	m_selectionLine.update();
	m_selectionLine.setNewTarget(m_markedIndex);
	ModelHandlerMutant& lastSelectedModelHandler = static_cast<ModelHandlerMutant&>(m_mutants[m_lastMarkedIndex]->getModelHandler());
	if (m_lastMarkedIndex != m_markedIndex)
		static_cast<ModelHandlerMutant&>(m_mutants[m_lastMarkedIndex]->getModelHandler()).setHovered(false);
	static_cast<ModelHandlerMutant&>(m_mutants[m_markedIndex]->getModelHandler()).setHovered(true);
	m_lastMarkedIndex = m_markedIndex;

	m_energyCostOfCurrentlyMarked = energyCostOf(currentNode, static_cast<ModelHandlerMutant&>(m_mutants[m_markedIndex]->getModelHandler()).getPolarCoordinates());
}
void PlayerHandlerStateSelectionHandler::handleIndex(const OIS::KeyEvent& e)
{
	int idxVelocity = 0;
	if (e.key == OIS::KC_A)
		idxVelocity--;
	if (e.key == OIS::KC_D)
		idxVelocity++;
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
	if (m_mutants.size() == m_attackListConst.size())
		return;
	m_markedIndex += iVel;
	if (m_markedIndex < 0)
	{
		m_markedIndex = m_mutants.size()-1;
		iVel = -1;
	}
	else if (m_markedIndex > m_mutants.size() - 1)
	{
		m_markedIndex = 0;
		iVel = +1;
	}
	if (isInList(m_markedIndex))
        changeIndex(iVel);
}
bool PlayerHandlerStateSelectionHandler::isInList(int elm)
{
	for (int i = 0; i < m_attackListConst.size(); i++)
	{
		if (m_attackListConst[i]== elm)
			return true;
	}
	return false;
}
void PlayerHandlerStateSelectionHandler::extremeChangeIndex(int iVel, int move)
{
	if (m_mutants.size() == m_attackListConst.size())
		return;
	if (iVel > 0)
	{
		if (!isInList(m_mutants.size() - 1 - move))
			m_markedIndex = m_mutants.size() - 1 - move;
		else
			extremeChangeIndex(iVel, ++move);
	}
	else
	{
		if (!isInList(0 + move))
			m_markedIndex = 0 + move;
		else
			extremeChangeIndex(iVel, ++move);
	}
}
int PlayerHandlerStateSelectionHandler::getMarked() const
{
	return m_markedIndex;
}
int PlayerHandlerStateSelectionHandler::getEnergyCostOfMarked() const
{
	return m_energyCostOfCurrentlyMarked;
}
void PlayerHandlerStateSelectionHandler::addLine()
{
	m_selectionLine.addEnemy();
}