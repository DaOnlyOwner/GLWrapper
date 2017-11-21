#pragma once
#include "VBO.h"
#include "Mesh.h"
#include "Singleton.h"


namespace doo
{
	namespace gl
	{
		class MeshManager : public Singleton<MeshManager>
		{
		public:
			friend class Singleton<MeshManager>;
			void BeginStaticGeometry();
			std::pair<u32, u32> AddStaticGeometry(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices);
			void EndStaticGeometry();

			const InterleavedLayout& GetStandardInterleavedLayout() const
			{
				return m_standardInterleaved;
			}

		private:
			MeshManager();
			VboId m_staticGeometry;
			std::vector<Vertex> m_verticesStaticGeometry;
			std::vector<u32> m_indicesStaticGeometry;
			bool m_canAddStaticGeometry;

			InterleavedLayout m_standardInterleaved;


		};

	}
}

