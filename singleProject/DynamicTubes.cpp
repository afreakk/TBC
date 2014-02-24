#include "stdafx.h"
#include "DynamicTubes.h"
#include "OgreCore.h"
#include "../procedural/Procedural.h"



DynamicTubes::DynamicTubes()
{
}


DynamicTubes::~DynamicTubes()
{
	OgreCore::getSingleton().getSceneMgr()->destroyManualObject(m_manObj);
	OgreCore::getSingleton().getSceneMgr()->destroySceneNode(m_node);
}

void DynamicTubes::create(const Ogre::Node* playerNode)
{
	Ogre::Real height = 5.0;
	Ogre::Real width = 25.0;
	m_spline = Procedural::RoundedCornerSpline2().setNumSeg(2);
	m_spline.addPoint(-width, -height);
	m_spline.addPoint(width, -height);
	m_spline.addPoint(width, height);
	m_spline.addPoint(-width, height);
	m_spline.close();

	// The shape that will be extruded along the path
	m_shape =m_spline.realizeShape();//Procedural::CircleShape().setNumSeg(4).setRadius(5.0).realizeShape();
	m_nodes.push_back(playerNode);
	// This is an example use of a shape texture track, 
	// which specifies how texture coordinates should be mapped relative to the shape points
	textureTrack = Procedural::Track(Procedural::Track::AM_POINT).addKeyFrame(0, 0).addKeyFrame(2, .2f).addKeyFrame(3, .8f).addKeyFrame(5, 1);
	// The extruder actually creates the road mesh from all parameters
	addPoints();
	m_extruder = Procedural::Extruder().setExtrusionPath(&m_path).setShapeToExtrude(&m_shape).setShapeTextureTrack(&textureTrack).setUTile(20.f);
	m_manObj = m_extruder.realizeDynamicManualObject("PathIndicator");
	putMesh(m_manObj,Ogre::Vector3(0.0,height,0.0));
}
void DynamicTubes::addPoints()
{
	m_path = Procedural::Path();
	for (const auto & i : m_nodes)
		m_path.addPoint(i->getPosition());
	while (m_path.getPoints().size() < 1)
		m_path.addPoint(m_nodes.back()->getPosition().randomDeviant(Radian(Math::PI*2.0)));
}
void DynamicTubes::makePath()
{
	addPoints();
	m_extruder.setExtrusionPath(&m_path);
}
void DynamicTubes::refreshLatestNode(Ogre::Node* node)
{
	m_nodes.back() = node;
}
void DynamicTubes::insertNode(Ogre::Node* node, int index)
{
	if (index == -1)
	    m_nodes.push_back(node);
	else
	{
        assert(index < m_nodes.size() && index > 0);
		m_nodes[index] = node;
	}
}
void DynamicTubes::update()
{
	if (m_nodes.size() < 2)
		return;
	makePath();
	m_extruder.updateManualObject();
}
void DynamicTubes::putMesh(Ogre::ManualObject* mesh, const Vector3& position, bool castShadows)
{
	m_node = OgreCore::getSingleton().getSceneMgr()->getRootSceneNode()->createChildSceneNode();
	m_node->attachObject(mesh);
	m_node->setPosition(position+Vector3(0.0,0.0,0.0));
	mesh->setCastShadows(castShadows);
}
