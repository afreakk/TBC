#pragma once
#include "OgreSingleton.h"
#include "ManualLine.h"
class TBCRay : public Ogre::Singleton<TBCRay>
{
private:
	Ogre::RaySceneQuery* m_raySceneQuery;//!< Ray query

public:
	TBCRay(Ogre::SceneManager* sceneMgr);
	bool RaycastPlayer(const Ogre::Vector3& point, const Ogre::Vector3& normal);
	bool RaycastFromPoint(const Ogre::Vector3& point, const Ogre::Vector3& normal, Ogre::Vector3& result);

private:
	static void GetMeshInformation(const Ogre::MeshPtr mesh, size_t &vertex_count, Ogre::Vector3*& vertices, size_t& index_count, unsigned long*& indices, const Ogre::Vector3& position, const Ogre::Quaternion& orient, const Ogre::Vector3& scale);
	static void GetMeshInformation(const Ogre::Entity* entity, size_t& vertex_count, Ogre::Vector3*& vertices, size_t& index_count, unsigned long*& indices, const Ogre::Vector3& position, const Ogre::Quaternion& orient, const Ogre::Vector3& scale);
	void debugRay(const Ogre::Vector3& point, const Ogre::Vector3& normal);
	void debugHit(const Ogre::Vector3& point, const Ogre::Vector3& endPoint);
	bool checkVertex(Ogre::RaySceneQueryResultEntry& rayResult, Vector3& closest_result, Ogre::Ray& ray, Ogre::Real& closest_distance);
	bool checkVertexLevel(Ogre::Real& closest_distance, Vector3* vertices,unsigned long* indices, size_t vertex_count, size_t index_count, Ogre::Ray& ray);

	ManualLine m_hitLine;
	ManualLine m_line;
	Ogre::Ray ray;
};

