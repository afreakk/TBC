#include "stdafx.h"
#include "PlayerSelectionLine.h"


PlayerSelectionLine::PlayerSelectionLine(Ogre::Node* baseNode, const Ogre::Real& spacing)
: m_spacing(spacing)
{
	pushBack(baseNode);
}


PlayerSelectionLine::~PlayerSelectionLine()
{
}

void PlayerSelectionLine::updateBack(Ogre::Node* node)
{
	if (m_nodes.size() < 2)
		pushBack(node);
	m_nodes.back().first = node->getName();
	m_nodes.back().second = node;
}
void PlayerSelectionLine::addNode(Ogre::Node* node)
{
	pushBack(node);
}
void PlayerSelectionLine::pushBack(Ogre::Node* node)
{
	std::pair<string, Node*> newElement;
	newElement.first = node->getName();
	newElement.second = node;
	m_nodes.push_back( newElement);
}
void PlayerSelectionLine::removeNode(const std::string& name)
{
	auto elmnt = findElement(name);
	m_nodes.erase(findElement(name));
}
std::vector<std::pair<std::string, Ogre::Node*> >::iterator PlayerSelectionLine::findElement(const std::string& name)
{
	for (auto itt = m_nodes.begin(); itt != m_nodes.end(); ++itt)
	{
		if ((*itt).first == name)
			return itt;
	}
	assert(0);
	return m_nodes.begin();
}
void PlayerSelectionLine::update(const Ogre::Real& energyCostScale)
{
    const Vector3& localPosFrom = Vector3::ZERO;
	while (m_nodes.size() < m_lines.size() + 1)
		m_lines.pop_back();
	unsigned j = 0;
	for (unsigned i = 0; i < m_nodes.size()-1; i ++)
	{
		if (m_nodes[i] == m_nodes[i + 1])
			continue;
		Vector3 localPosTo = m_nodes[i].second->convertWorldToLocalPosition(m_nodes[i+1].second->getPosition())+Vector3(0,1,0);
		if (j+1 > m_lines.size())
            m_lines.emplace_back(unique_ptr<StapledLine>(new StapledLine(static_cast<SceneNode*>(m_nodes[i].second),m_spacing)), 
			unique_ptr<BillboardNumber>(new BillboardNumber(static_cast<SceneNode*>(m_nodes[i].second))));
		if (m_lines[j].first->getParentNode() != m_nodes[i].second)
		{
			m_lines[j].first->setParentSceneNode(static_cast<Ogre::SceneNode*>(m_nodes[i].second));
			m_lines[j].second->setParentNode(static_cast<Ogre::SceneNode*>(m_nodes[i].second));
		}
		m_lines[j].first->setLine(localPosFrom, localPosTo);
		m_lines[j].second->markAs(i);
		j++;
	}
	while (j < m_lines.size())
	{
		m_lines[j].first->setLine(Vector3::ZERO, Vector3::ZERO);
		m_lines[j++].second->unMarkNumber();
	}
	if (!m_lines.empty())
	{
        m_lines.back().first->setColourScale(energyCostScale);
	}
}
