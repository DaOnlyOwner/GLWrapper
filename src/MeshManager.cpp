#include "tools3d/MeshManager.h"


namespace doo
{
	namespace gl
	{
		MeshManager::MeshManager(): m_standardInterleaved(2)
		{
			m_standardInterleaved.Add(3).Add(3);
		}

		void MeshManager::BeginStaticGeometry()
		{
			m_canAddStaticGeometry = true;
		}

		std::pair<u32, u32> MeshManager::AddStaticGeometry(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices)
		{
			// TODO: Proper error handling
			assert(m_canAddStaticGeometry);

			u32 offsetVBO = m_verticesStaticGeometry.size() -1;
			u32 offsetEBO = m_verticesStaticGeometry.size() -1;

			m_verticesStaticGeometry.insert(m_verticesStaticGeometry.end(), p_vertices.begin(), p_vertices.end());
			m_indicesStaticGeometry.insert(m_indicesStaticGeometry.end(), p_indices.begin(), p_indices.end());

			return std::make_pair(offsetVBO, offsetEBO);

		}

		void MeshManager::EndStaticGeometry()
		{
			m_canAddStaticGeometry = false;
			const VertexLayoutInfo* layoutInfo = m_standardInterleaved.GetInterleavedLayoutInfo();


			CreateVBOFromVector(m_verticesStaticGeometry, m_indicesStaticGeometry, layoutInfo, m_standardInterleaved.GetNumAttribPtrs(), GL_STATIC_DRAW);

			m_indicesStaticGeometry.clear();
			m_indicesStaticGeometry.shrink_to_fit();

			m_verticesStaticGeometry.clear();
			m_verticesStaticGeometry.shrink_to_fit();

		}

	}
}

