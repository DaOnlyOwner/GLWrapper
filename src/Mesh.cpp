#include "tools3d/Mesh.h"
#include "MeshManager.h"
#include <cassert>


namespace doo
{

	namespace gl
	{
		Mesh::Mesh(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices, const std::string& p_name, bool p_isStatic) : m_name(p_name), m_isStatic(p_isStatic) 
		{
			if(p_isStatic)
			{
				std::pair<u32,u32> vert_indices = MeshManager::Instance().AddStaticGeometry(p_vertices, p_indices);
				m_indexCount = p_indices.size();
				m_offsetIntoVBO = vert_indices.first;
				m_offsetIntoEBO = vert_indices.second;
			}
			
			
			// TODO: Else case missing
			assert(!p_isStatic);
		}

		void Mesh::BeginStaticGeometry()
		{
			MeshManager::Instance().BeginStaticGeometry();
		}

		void Mesh::EndStaticGeometry()
		{
			MeshManager::Instance().EndStaticGeometry();
		}
	}

}
