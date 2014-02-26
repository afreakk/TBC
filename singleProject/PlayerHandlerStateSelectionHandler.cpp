#include "stdafx.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "ModelHandlerMutant.h"
#include "MutantContainer.h"

const std::string NONE_STRING = "NONE";
const Ogre::Real maxTheta = Math::PI*2.0;
const Ogre::Real minTheta = 0.0;

PlayerHandlerStateSelectionHandler::PlayerHandlerStateSelectionHandler( const std::vector<std::string>& attackList)
: m_currentMarked{ nullptr }
, m_prevMarked(nullptr)
, m_energyCostOfCurrentlyMarked(0)
, m_attackListConst(attackList)
{
    changeMarkedMutants(true);
}


PlayerHandlerStateSelectionHandler::~PlayerHandlerStateSelectionHandler()
{
	if (m_currentMarked)
        static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).setHovered(selectedType::DEFAULT);
    if (m_prevMarked)
        static_cast<ModelHandlerMutant&>(m_prevMarked->getModelHandler()).setHovered(selectedType::DEFAULT);
}

bool PlayerHandlerStateSelectionHandler::updateMarked(const PolarCoordinates& markedPolarCoordinates)
{
	bool markedChanged = false;
	if (m_prevMarked != m_currentMarked)
	{
		if (m_prevMarked)
		    static_cast<ModelHandlerMutant&>(m_prevMarked->getModelHandler()).setHovered(selectedType::UNHOVERED);
		if (m_currentMarked)
		{
            static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).setHovered(selectedType::HOVERED);
            markedChanged = true;
		}
	}
    m_energyCostOfCurrentlyMarked = energyCostOf(markedPolarCoordinates, static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).getPolarCoordinates());
	m_prevMarked = m_currentMarked;
	return markedChanged;
}

void PlayerHandlerStateSelectionHandler::handleKeys(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_A)
		changeMarkedMutants(false);
	if (e.key == OIS::KC_D)
		changeMarkedMutants(true);
}

void PlayerHandlerStateSelectionHandler::changeMarkedMutants(bool right)
{
    m_currentMarked = getNewMarkedMutant(right,m_currentMarked);
}
Mutant* PlayerHandlerStateSelectionHandler::getNewMarkedMutant(bool right, Mutant* currentMarked, unsigned mutantWasInListCount, NormalDirection directionOverflow)
{ 
    if (mutantWasInListCount >= MutantContainer::getSingleton().getMutantIt().size())
        return currentMarked;
	Real theta = getTheta(currentMarked,directionOverflow);
	Mutant* closestMutant;
	if (right)
	{
		closestMutant = MutantContainer::getSingleton().getClosestHigherThan(theta, currentMarked);
		if (!closestMutant)
            return getNewMarkedMutant(right,nullptr,mutantWasInListCount,NormalDirection::dirRight);
	}
	else
	{
		closestMutant = MutantContainer::getSingleton().getClosestLowerThan(theta, currentMarked);
		if (!closestMutant)
            return getNewMarkedMutant(right,nullptr,mutantWasInListCount,NormalDirection::dirLeft);
    }
	if (isInList(closestMutant->getModelHandler().getNode()->getName()))
        return getNewMarkedMutant(right,closestMutant,++mutantWasInListCount);
	return closestMutant;
}
const Ogre::Real PlayerHandlerStateSelectionHandler::getTheta(Mutant* currentMarked,NormalDirection directionOverflow) const
{
	Real theta = minTheta;
	switch (directionOverflow)
	{
	case NormalDirection::dirRight:
        theta = minTheta;
		break;
	case NormalDirection::dirLeft:
        theta = maxTheta;
		break;
	case NormalDirection::None:
        if (currentMarked)
            theta = currentMarked->getSelectionTheta();
		break;
	default:
		break;
	}
	return theta;
}

bool PlayerHandlerStateSelectionHandler::isInList(const std::string& elm)
{
	for (unsigned i = 0; i < m_attackListConst.size(); i++)
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
Mutant* PlayerHandlerStateSelectionHandler::getCurrentMarkedMutant() const
{

	return m_currentMarked;
}