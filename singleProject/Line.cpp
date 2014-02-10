#include "stdafx.h"
#include "Line.h"

#include "OgreCore.h"
const Vector3 LINEHEIGHT = Vector3(0.f,10.1f,0.f);
Line::Line(Node* start, Node* end, string materialName)
: m_start(start)
, m_end(end)
, m_line(m_start->getPosition()+LINEHEIGHT, m_end->getPosition()+LINEHEIGHT, materialName)
{
}

void Line::newNode(Node* end)
{
	m_end = end;
}

void Line::update()
{
	m_line.update(m_start->getPosition()+LINEHEIGHT, m_end->getPosition()+LINEHEIGHT);
}
Line::~Line()
{
}
