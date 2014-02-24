#pragma once
#include "../procedural/ProceduralExtruder.h"
#include "../procedural/ProceduralPath.h"
#include "../procedural/ProceduralPathGenerators.h"
#include "../procedural/ProceduralShapeGenerators.h"
namespace Ogre
{
	class ManualObject;
}
class DynamicTubes
{
public:
	DynamicTubes();
	~DynamicTubes();
	void create(const Ogre::Node* playerNode);
	void update();
	void insertNode(Ogre::Node* node, int index = -1);
	void refreshLatestNode(Ogre::Node*);
private:
	Procedural::Path m_path;
	Procedural::Extruder m_extruder;
	Procedural::RoundedCornerSpline2 m_spline;
	Procedural::Shape m_shape;
    Procedural::Track textureTrack;
	Ogre::ManualObject* m_manObj;
	std::vector<const Ogre::Node*> m_nodes;
	Ogre::SceneNode* m_node;

	void addPoints();
	void makePath();
	void putMesh(Ogre::ManualObject* mesh, const Ogre::Vector3& position=Ogre::Vector3::ZERO, bool castShadows=true);
};

