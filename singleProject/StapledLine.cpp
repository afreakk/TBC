#include "stdafx.h"
#include "StapledLine.h"
#include "UnitCircleMovement.h"


StapledLine::StapledLine(Ogre::SceneNode* sceneNode, const Ogre::Real& spacing)
: m_set(sceneNode)
, m_parentNode(sceneNode)
, m_numLines(0)
, m_colourScale(1.0)
, m_spacing(spacing)
{
}

Ogre::Node* StapledLine::getParentNode()
{
	return m_parentNode;
}

StapledLine::~StapledLine()
{
}

void StapledLine::setColourScale(const Ogre::Real& scale)
{
	m_colourScale = scale;
}

void StapledLine::refresh(unsigned numLines)
{
	int billboardToGet = numLines - static_cast<int>(m_numLines);
	if (billboardToGet < 0)
		destroyBillboards(numLines);
	else
	    getBillboards(static_cast<unsigned>(billboardToGet));
	m_numLines = numLines;
} 
void StapledLine::setLine(const Ogre::Vector3& from, const Ogre::Vector3& to)
{
	unsigned numLines = boost::numeric_cast<unsigned>(from.distance(to)/(m_set.getDimension()*m_spacing));
	Real clrScale = m_colourScale;
	Real increments = 1.0f / (boost::numeric_cast<Real>(numLines)/2.0f);
	if (m_numLines != numLines)
	    refresh(numLines);
	for (unsigned i = 0; i < numLines; i++)
	{
		Real lerpVal = ( boost::numeric_cast<Real>(i) + 0.5f) / ( boost::numeric_cast<Real>(numLines) - 0.5f );
		m_billboards[i]->setPosition(Math::lerp(from, to, lerpVal));
		m_billboards[i]->setColour(Ogre::ColourValue(0.0f,((clrScale>0.0f)?1.0f:0.0f),0.0f,1.0f));
		clrScale -= increments;
	}
}
void StapledLine::destroyBillboards(unsigned numLines)
{
	while (m_billboards.size() > numLines)
	{
		m_set.destroyBillboard(m_billboards.back());
		m_billboards.pop_back();
	}
}
void StapledLine::setParentSceneNode(Ogre::SceneNode* sceneNode)
{
	m_set.setSceneNode(sceneNode);
}
void StapledLine::getBillboards(unsigned count)
{
	for (unsigned i = 0; i < count; i++)
		m_billboards.push_back(m_set.getBillboard());
}