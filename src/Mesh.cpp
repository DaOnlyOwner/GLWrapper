#include "tools3d/Mesh.h"
#include "tools3d/VBO.h"
#include "tools3d/MeshManager.h"

namespace doo
{

	namespace gl
	{
		Mesh::Mesh(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices, const std::string& p_name)
		{
			MeshManager& instance = MeshManager::Instance();
			std::pair<u32,u32> vert_indices = instance.AddStaticGeometry(p_vertices, p_indices);
			m_indexCount = p_indices.size();
			m_offsetIntoVBO = vert_indices.first;
			m_offsetIntoEBO = vert_indices.second;
		}
	}

}
