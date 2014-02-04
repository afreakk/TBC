#include "stdafx.h"
#include "PlayerHandlerStateSelectionLine.h"
#include "../Containers/MutantContainer.h"
#include "../Containers/PlayerContainer.h"

PlayerHandlerStateSelectionLine::PlayerHandlerStateSelectionLine()
: m_index(0)
, m_currentNode(PlayerContainer::getSingleton().getPlayer()->getNode())
{
	m_lines.emplace_back(new Line(m_currentNode, m_currentNode));
}

void PlayerHandlerStateSelectionLine::setNewTarget(unsigned index)
{
	m_currentNode = MutantContainer::getSingleton().getMutants()[index]->getNode();
	m_lines[m_index]->newNode(m_currentNode);
}

void PlayerHandlerStateSelectionLine::addEnemy()
{
	m_lines.emplace_back(new Line(m_currentNode, m_currentNode));
	m_index++;
}
void PlayerHandlerStateSelectionLine::update()
{
	for (auto& line : m_lines)
		line->update();
}
PlayerHandlerStateSelectionLine::~PlayerHandlerStateSelectionLine()
{
}