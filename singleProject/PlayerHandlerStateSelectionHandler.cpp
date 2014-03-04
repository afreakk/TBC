#include "stdafx.h"
#include "PlayerHandlerStateSelectionHandler.h"
#include "ModelHandlerMutant.h"
#include "MutantContainer.h"
#include "LaneSettings.h"

const std::string NONE_STRING = "NONE";
const Ogre::Real maxTheta = Math::PI*2.0f;
const Ogre::Real minTheta = 0.0f;

PlayerHandlerStateSelectionHandler::PlayerHandlerStateSelectionHandler( const std::vector<std::string>& attackList)
: m_currentMarked{ nullptr }
, m_prevMarked(nullptr)
, m_energyCostOfCurrentlyMarked(0)
, m_attackListConst(attackList)
, m_laneIdx(LaneSettings::getSingleton().getLaneCount()-1 )
{
    changeMarkedMutant(true);
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
	if (m_currentMarked)
        m_energyCostOfCurrentlyMarked = energyCostOf(markedPolarCoordinates, static_cast<ModelHandlerMutant&>(m_currentMarked->getModelHandler()).getPolarCoordinates());
	m_prevMarked = m_currentMarked;
	return markedChanged;
}

void PlayerHandlerStateSelectionHandler::handleKeys(const OIS::KeyEvent& e)
{
	if (e.key == OIS::KC_S)
		changeMarkedMutant(true,false,false);
	if (e.key == OIS::KC_W)
		changeMarkedMutant(true,false,true);
	if (e.key == OIS::KC_A)
		changeMarkedMutant(false);
	if (e.key == OIS::KC_D)
		changeMarkedMutant(true);
}

void PlayerHandlerStateSelectionHandler::changeLaneIdx(bool up)
{
	if (up)
	{
		if (m_laneIdx > 0)
			m_laneIdx--;
		else
			m_laneIdx = static_cast<int>(LaneSettings::getSingleton().getLaneCount()) - 1;
	}
	else
	{
		if (m_laneIdx < static_cast<int>(LaneSettings::getSingleton().getLaneCount()) - 1)
			m_laneIdx++;
		else
			m_laneIdx = 0;
	}
}
void PlayerHandlerStateSelectionHandler::changeMarkedMutant(bool right, bool horizontal, bool up)
{
	if (!horizontal)
		changeLaneIdx(up);
	auto oldMarked = m_currentMarked;
    m_currentMarked = getNewMarkedMutant(right,m_currentMarked,horizontal);
	unsigned times = 0;
    while ((oldMarked == m_currentMarked || isInList(m_currentMarked->getModelHandler().getNode()->getName())) && times  < LaneSettings::getSingleton().getLaneCount())
    {
		changeLaneIdx(up);
        m_currentMarked = getNewMarkedMutant(right,m_currentMarked,horizontal);
		times++;
    }
}
Mutant* PlayerHandlerStateSelectionHandler::getNewMarkedMutant(bool right, Mutant* currentMarked, bool horizontal, unsigned mutantWasInListCount
	, NormalDirection directionOverflow	, unsigned spunAroundCount)
{ 
	MutantContainer& mutantContainer = MutantContainer::getSingleton();
    if (mutantWasInListCount >= mutantContainer.getMutantIt().size() || spunAroundCount > 1)
        return currentMarked;
	Real theta = getTheta(currentMarked,directionOverflow);
	Mutant* closestMutant;
	if (horizontal)
	{
        if (right)
        {
            closestMutant = mutantContainer.getClosestHigherThanRadiusBased(theta, LaneSettings::getSingleton().getLane(m_laneIdx),currentMarked);
			if (!closestMutant)
			{
				closestMutant = mutantContainer.getClosestHigherThan(theta, currentMarked);
				if (!closestMutant)
					return getNewMarkedMutant(right, nullptr, horizontal, mutantWasInListCount, NormalDirection::dirRight, ++spunAroundCount);
				else
					m_laneIdx = LaneSettings::getSingleton().getClosestLane(closestMutant->getNode()->getPosition());
			}
        }
        else
        {
            closestMutant = mutantContainer.getClosestLowerThanRadiusBased(theta, LaneSettings::getSingleton().getLane(m_laneIdx), currentMarked);
			if (!closestMutant)
			{
				closestMutant = mutantContainer.getClosestLowerThan(theta, currentMarked);
				if (!closestMutant)
					return getNewMarkedMutant(right, nullptr, horizontal, mutantWasInListCount, NormalDirection::dirLeft, ++spunAroundCount);
				else
					m_laneIdx = LaneSettings::getSingleton().getClosestLane(closestMutant->getNode()->getPosition());
			}
        }
	}
	else
	{
		closestMutant = mutantContainer.getClosestRadiusBased(theta, LaneSettings::getSingleton().getLane(m_laneIdx), currentMarked);
		if (!closestMutant)
			return currentMarked;
	}
	if (isInList(closestMutant->getModelHandler().getNode()->getName()))
        return getNewMarkedMutant(right,closestMutant, horizontal, ++mutantWasInListCount);
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