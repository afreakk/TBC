#include "stdafx.h"
#include "PlayerSelectionLine.h"


PlayerSelectionLine::PlayerSelectionLine(Ogre::Node* baseNode, const Ogre::Real& spacing)
: m_spacing(spacing)
{
	m_nodes.push_back(baseNode);
	m_nodes.push_back(baseNode);
}


PlayerSelectionLine::~PlayerSelectionLine()
{
}

void PlayerSelectionLine::updateBack(Ogre::Node* node)
{
	m_nodes.back() = node;
}
void PlayerSelectionLine::addNode(Ogre::Node* node)
{
	m_nodes.push_back(node);
}
void PlayerSelectionLine::update(const Ogre::Real& energyCostScale)
{
    const Vector3& localPosFrom = Vector3::ZERO;
	for (unsigned i = 0; i < m_nodes.size()-1; i ++)
	{
		if (m_nodes[i] == m_nodes[i + 1])
			continue;
		Vector3 localPosTo = m_nodes[i]->convertWorldToLocalPosition(m_nodes[i+1]->getPosition());
		if (i + 1 > m_lines.size())
            m_lines.emplace_back(new StapledLine(static_cast<SceneNode*>(m_nodes[i]),m_spacing));
		m_lines[i]->setLine(localPosFrom, localPosTo);
	}
	if (!m_lines.empty())
        m_lines.back()->setColourScale(energyCostScale);
}