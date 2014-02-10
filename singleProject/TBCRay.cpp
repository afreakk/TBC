#include "stdafx.h"
#include "TBCRay.h"
#include "OgreRay.h"
#include "ManualLine.h"
#include "ModelRecipe.h"
template<> TBCRay* Ogre::Singleton<TBCRay>::msSingleton = 0;
TBCRay::TBCRay(Ogre::SceneManager* sceneMgr)
{
	MovableObject::setDefaultQueryFlags(QueryMasks::None);
	m_raySceneQuery = sceneMgr->createRayQuery(Ogre::Ray(), QueryMasks::PlayerMask | QueryMasks::World);
	if (!m_raySceneQuery)
		printf("["__FILE__"::%u] Failed to create Ogre::RaySceneQuery instance\n", __LINE__);
	m_raySceneQuery->setSortByDistance(true);

	m_line.init(Vector3::ZERO, Vector3::ZERO, "Green");
	m_hitLine.init(Vector3::ZERO, Vector3::ZERO, "Red");
}


/***************************************************************************//*!
																			 * @brief Raycast from a point in to the scene.
																			 * @param[in] point		Point to analyse
																			 * @param[in] normal		Direction
																			 * @param[out] result	Result ( ONLY if return TRUE )
																			 * @return TRUE if somethings found => {result} NOT EMPTY
																			 */
void TBCRay::debugRay(const Ogre::Vector3& point, const Ogre::Vector3& normal)
{
	m_line.update(point, point + normal);
}
void TBCRay::debugHit(const Ogre::Vector3& point, const Ogre::Vector3& endPoint)
{
	m_hitLine.update(point, endPoint);
}

bool TBCRay::RaycastPlayer(const Ogre::Vector3& point, const Ogre::Vector3& normal)
{
	debugRay(point, normal);
	Ogre::Ray ray(point, normal.normalisedCopy());
	// create a query object
	m_raySceneQuery->setRay(ray);

	// execute the query, returns a vector of hits
//	m_raySceneQuery->setQueryMask(QueryMasks::PlayerMask);
	if (m_raySceneQuery->execute().size() <= 0)
		// raycast did not hit an objects bounding box
		return false;
	Ogre::RaySceneQueryResult& hitObjects = m_raySceneQuery->getLastResults();
	if (hitObjects.size()<1)
		return false;

	Ogre::RaySceneQueryResultEntry& firstHitObject = hitObjects[0];

	if (!firstHitObject.movable && firstHitObject.movable->getMovableType() != "Entity")
		return false;
    Ogre::Entity *pentity = static_cast<Ogre::Entity*>(firstHitObject.movable);
	String entityName= pentity->getName();
	if (entityName != "PlayerEntity")
		return false;
	else
	{
        // mesh data to retrieve
        size_t vertex_count;
        size_t index_count;
        Ogre::Vector3* vertices;
        unsigned long* indices;

        GetMeshInformation(pentity, vertex_count, vertices, index_count, indices, pentity->getParentNode()->_getDerivedPosition()
            , pentity->getParentNode()->_getDerivedOrientation(), pentity->getParentNode()->_getDerivedScale());
        // test for hitting individual triangles on the mesh
        for (int i = 0; i<static_cast<int>(index_count); i += 3)
        {
            // check for a hit against this triangle
            std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]], true, false);
            if (hit.second)
                return true;
        }
        delete[] vertices;
        delete[] indices;
	}
	return false;
}
bool TBCRay::RaycastFromPoint(const Ogre::Vector3& point, const Ogre::Vector3& normal, Ogre::Vector3& result)
{
	debugRay(point, normal);
	// create the ray to test
	Ogre::Ray ray(point, normal);

	if (!m_raySceneQuery)
		return false;

//	 m_raySceneQuery->setQueryMask(~QueryMasks::None);
	// create a query object
	m_raySceneQuery->setRay(ray);

	// execute the query, returns a vector of hits
	if (m_raySceneQuery->execute().size() <= 0)
		// raycast did not hit an objects bounding box
		return false;

	// at this point we have raycast to a series of different objects bounding boxes.
	// we need to test these different objects to see which is the first polygon hit.
	// there are some minor optimizations (distance based) that mean we wont have to
	// check all of the objects most of the time, but the worst case scenario is that
	// we need to test every triangle of every object.
	Ogre::Real closest_distance = -1.0f;
	Ogre::Vector3 closest_result;
	Ogre::RaySceneQueryResult& query_result = m_raySceneQuery->getLastResults();
	for (size_t qr_idx = 0, size = query_result.size(); qr_idx<size; ++qr_idx)
	{
        
		// stop checking if we have found a raycast hit that is closer
		// than all remaining entities
		if (closest_distance >= 0.0f && closest_distance < query_result[qr_idx].distance)
			break;
		if (query_result[qr_idx].movable->getName() == "PlayerEntity")
		{
			result = query_result[qr_idx].movable->getParentNode()->getPosition();
            debugHit(point, query_result[qr_idx].movable->getParentNode()->getPosition());
			return true;
		}
		if (checkVertex(query_result[qr_idx], closest_result, ray, closest_distance))
		{
            closest_result = ray.getPoint(closest_distance);
            debugHit(point, query_result[qr_idx].movable->getParentNode()->getPosition());
		}
	}

	// return the result
	if (closest_distance >= 0.0f){
		// raycast success
		result = closest_result;
		return true;
	}
	// raycast failed
	return false;
}
bool TBCRay::checkVertex(Ogre::RaySceneQueryResultEntry& rayResult , Vector3& closest_result, Ogre::Ray& ray, Ogre::Real& closest_distance)
{

	if (!rayResult.movable)
		return false;
    const std::string& movableType = rayResult.movable->getMovableType();
    // mesh data to retrieve
    size_t vertex_count;
    size_t index_count;
    Ogre::Vector3* vertices;
    unsigned long* indices;
    if (movableType == "Entity"){
        // get the entity to check
        Ogre::Entity *pentity = static_cast<Ogre::Entity*>(rayResult.movable);
        // get the mesh information
        GetMeshInformation(pentity, vertex_count, vertices, index_count, indices,
            pentity->getParentNode()->_getDerivedPosition(),
            pentity->getParentNode()->_getDerivedOrientation(),
            pentity->getParentNode()->_getDerivedScale()
            );
    }
    else{
        return false;
    }

    // test for hitting individual triangles on the mesh
	bool new_closest_found = checkVertexLevel(closest_distance, vertices, indices, vertex_count, index_count,ray);
    // free the verticies and indicies memory
    delete[] vertices;
    delete[] indices;

    // if we found a new closest raycast for this object, update the
    // closest_result before moving on to the next object.
	return new_closest_found;
}

bool TBCRay::checkVertexLevel(Ogre::Real& closest_distance, Vector3* vertices,unsigned long* indices, size_t vertex_count, size_t index_count, Ogre::Ray& ray)
{

    bool new_closest_found = false;
    for (int i = 0; i<static_cast<int>(index_count); i += 3)
    {
        // check for a hit against this triangle
        std::pair<bool, Ogre::Real> hit = Ogre::Math::intersects(ray, vertices[indices[i]], vertices[indices[i + 1]], vertices[indices[i + 2]], true, false);

        // if it was a hit check if its the closest
        if (hit.first && (closest_distance < 0.0f || hit.second < closest_distance))
        {
            // this is the closest so far, save it off
            closest_distance = hit.second;
            new_closest_found = true;
        }
    }
	return new_closest_found;
}
void TBCRay::GetMeshInformation(const Ogre::Entity* entity, size_t& vertex_count, Ogre::Vector3*& vertices, size_t& index_count, unsigned long*& indices, const Ogre::Vector3& position, const Ogre::Quaternion& orient, const Ogre::Vector3& scale)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;
	vertex_count = index_count = 0;

	Ogre::MeshPtr mesh = entity->getMesh();


	bool useSoftwareBlendingVertices = entity->hasSkeleton();

	if (useSoftwareBlendingVertices)
		const_cast<Ogre::Entity*>(entity)->_updateAnimation();

	// Calculate how many vertices and indices we're going to need
	for (unsigned short i = 0, size = mesh->getNumSubMeshes(); i<size; ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);

		// We only need to add the shared vertices once
		if (submesh->useSharedVertices){
			if (!added_shared){
				vertex_count += mesh->sharedVertexData->vertexCount;
				added_shared = true;
			}
		}
		else{
			vertex_count += submesh->vertexData->vertexCount;
		}

		// Add the indices
		index_count += submesh->indexData->indexCount;
	}


	// Allocate space for the vertices and indices
	vertices = new Ogre::Vector3[vertex_count];
	indices = new unsigned long[index_count];

	added_shared = false;

	// Run through the submeshes again, adding the data into the arrays
	for (unsigned short i = 0, size = mesh->getNumSubMeshes(); i<size; ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);

		//----------------------------------------------------------------
		// GET VERTEXDATA
		//----------------------------------------------------------------

		//Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;
		Ogre::VertexData* vertex_data;

		//When there is animation:
		if (useSoftwareBlendingVertices)
			vertex_data = submesh->useSharedVertices ? entity->_getSkelAnimVertexData() : entity->getSubEntity(i)->_getSkelAnimVertexData();
		else
			vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;


		if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
		{
			if (submesh->useSharedVertices){
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);

			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

			// There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
			//  as second argument. So make it float, to avoid trouble when Ogre::Real will
			//  be comiled/typedefed as double:
			//      Ogre::Real* pReal;
			float* pReal = 0;

			for (size_t j = 0; j<vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);
				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
				vertices[current_offset + j] = (orient * (pt * scale)) + position;
			}

			vbuf->unlock();
			next_offset += vertex_data->vertexCount;
		}


		Ogre::IndexData* index_data = submesh->indexData;
		size_t numTris = index_data->indexCount / 3;
		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;

		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


		size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;
		size_t index_start = index_data->indexStart;
		size_t last_index = numTris * 3 + index_start;

		if (use32bitindexes){
			for (size_t k = index_start; k<last_index; ++k)
				indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
		}
		else{
			for (size_t k = index_start; k<last_index; ++k)
				indices[index_offset++] =
				static_cast<unsigned long>(pShort[k]) +
				static_cast<unsigned long>(offset);
		}

		ibuf->unlock();
		current_offset = next_offset;
	}
}

// Get the mesh information for the given mesh.
// Code found in Wiki: www.ogre3d.org/wiki/index.php/RetrieveVertexData
void TBCRay::GetMeshInformation(const Ogre::MeshPtr mesh, size_t &vertex_count, Ogre::Vector3*& vertices, size_t& index_count, unsigned long*& indices, const Ogre::Vector3& position, const Ogre::Quaternion& orient, const Ogre::Vector3& scale)
{
	bool added_shared = false;
	size_t current_offset = 0;
	size_t shared_offset = 0;
	size_t next_offset = 0;
	size_t index_offset = 0;

	vertex_count = index_count = 0;

	// Calculate how many vertices and indices we're going to need
	for (unsigned short i = 0, size = mesh->getNumSubMeshes(); i<size; ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);

		// We only need to add the shared vertices once
		if (submesh->useSharedVertices){
			if (!added_shared){
				vertex_count += mesh->sharedVertexData->vertexCount;
				added_shared = true;
			}
		}
		else{
			vertex_count += submesh->vertexData->vertexCount;
		}

		// Add the indices
		index_count += submesh->indexData->indexCount;
	}


	// Allocate space for the vertices and indices
	vertices = new Ogre::Vector3[vertex_count];
	indices = new unsigned long[index_count];

	added_shared = false;

	// Run through the submeshes again, adding the data into the arrays
	for (unsigned short i = 0, size = mesh->getNumSubMeshes(); i<size; ++i)
	{
		Ogre::SubMesh* submesh = mesh->getSubMesh(i);
		Ogre::VertexData* vertex_data = submesh->useSharedVertices ? mesh->sharedVertexData : submesh->vertexData;

		if ((!submesh->useSharedVertices) || (submesh->useSharedVertices && !added_shared))
		{
			if (submesh->useSharedVertices){
				added_shared = true;
				shared_offset = current_offset;
			}

			const Ogre::VertexElement* posElem = vertex_data->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			Ogre::HardwareVertexBufferSharedPtr vbuf = vertex_data->vertexBufferBinding->getBuffer(posElem->getSource());

			unsigned char* vertex = static_cast<unsigned char*>(vbuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));

			// There is _no_ baseVertexPointerToElement() which takes an Ogre::Real or a double
			//  as second argument. So make it float, to avoid trouble when Ogre::Real will
			//  be comiled/typedefed as double:
			//      Ogre::Real* pReal;
			float* pReal;

			for (size_t j = 0; j < vertex_data->vertexCount; ++j, vertex += vbuf->getVertexSize())
			{
				posElem->baseVertexPointerToElement(vertex, &pReal);
				Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);
				vertices[current_offset + j] = (orient * (pt * scale)) + position;
			}

			vbuf->unlock();
			next_offset += vertex_data->vertexCount;
		}


		Ogre::IndexData* index_data = submesh->indexData;
		size_t numTris = index_data->indexCount / 3;
		Ogre::HardwareIndexBufferSharedPtr ibuf = index_data->indexBuffer;
		if (ibuf.isNull()) continue; // need to check if index buffer is valid (which will be not if the mesh doesn't have triangles like a pointcloud)

		bool use32bitindexes = (ibuf->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		unsigned long*  pLong = static_cast<unsigned long*>(ibuf->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*>(pLong);


		size_t offset = (submesh->useSharedVertices) ? shared_offset : current_offset;
		size_t index_start = index_data->indexStart;
		size_t last_index = numTris * 3 + index_start;

		if (use32bitindexes){
			for (size_t k = index_start; k<last_index; ++k)
			{
				indices[index_offset++] = pLong[k] + static_cast<unsigned long>(offset);
			}

		}
		else{
			for (size_t k = index_start; k<last_index; ++k)
			{
				indices[index_offset++] =
					static_cast<unsigned long>(pShort[k]) +
					static_cast<unsigned long>(offset);
			}
		}

		ibuf->unlock();
		current_offset = next_offset;
	}
}

