#include "stdafx.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "ModelHandlerMutant.h"
#include "MutantContainer.h"

const std::string NONE_STRING = "NONE";
const Ogre::Real maxTheta = Math::PI*2.0;
const Ogre::Real minTheta = 0.0;

PlayerHandlerStateSelectionHandler::PlayerHandlerStateSelectionHandler( const std::vector<std::string>& attackList)
: m_currentMarked(nullptr)
, m_prevMarked(nullptr)
, m_energyCostOfCurrentlyMarked(0)
, m_attackListConst(attackList)
, m_currentTheta(&minTheta)
{
}


PlayerHandlerStateSelectionHandler::~PlayerHandlerStateSelectionHandler()
{
}

bool PlayerHandlerStateSelectionHandler::updateMarked(const PolarCoordinates& currentNode)
{
	bool markedChanged = false;
	m_selectionLine.update();
	if (m_prevMarked != m_currentMarked)
	{
		if (m_prevMarked)
		    static_cast<ModelHandlerMutant&>(m_prevMarked->getModelHandler()).setHovered(false);
		if (m_currentMarked)
		{
            static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).setHovered(true);
            m_selectionLine.setNewTarget(m_currentMarked->getNode());
            m_energyCostOfCurrentlyMarked = energyCostOf(currentNode, static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).getPolarCoordinates());
            markedChanged = true;
		}
	}
	m_prevMarked = m_currentMarked;
	return markedChanged;
}
void PlayerHandlerStateSelectionHandler::handleIndex(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_A)
		changeIndex(false);
	if (e.key == OIS::KC_D)
		changeIndex(true);
}
void PlayerHandlerStateSelectionHandler::changeIndex(bool right)
{ 
	if (m_attackListConst.size() >= MutantContainer::getSingleton().getMutantIt().size())
		return;
	if (right)
	{
		if ((m_currentMarked = MutantContainer::getSingleton().getClosestHigherThan(*m_currentTheta)) == nullptr)
		{
			m_currentTheta = &minTheta;
			changeIndex(right);
			return;
		}
	}
	else
	{
		if((m_currentMarked = MutantContainer::getSingleton().getClosestLowerThan(*m_currentTheta)) == nullptr)
		{
			m_currentTheta = &maxTheta;
			changeIndex(right);
			return;
		}
	}
	m_currentTheta = &(m_currentMarked->getPolarCoordinates().theta);
	if (isInList(m_currentMarked->getModelHandler().getNode()->getName()))
        changeIndex(right);
}


bool PlayerHandlerStateSelectionHandler::isInList(const std::string& elm)
{
	for (int i = 0; i < m_attackListConst.size(); i++)
	{
		if (m_attackListConst[i]== elm)
			return true;
	}
	return false;
}
const std::string& PlayerHandlerStateSelectionHandler::getMarked() const
{   
	if (m_currentMarked)
	{
		if (m_attackListConst.size() > 0 && m_currentMarked->getNode()->getName() == m_attackListConst.back())
			return NONE_STRING;
		return m_currentMarked->getModelHandler().getNode()->getName();
	}
	else
		return NONE_STRING;
}
int PlayerHandlerStateSelectionHandler::getEnergyCostOfMarked() const
{
	return m_energyCostOfCurrentlyMarked;
}
void PlayerHandlerStateSelectionHandler::addLine()
{
	m_selectionLine.addEnemy();
}