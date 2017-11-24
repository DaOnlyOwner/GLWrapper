#pragma once
#include "tools3d/VBO.h"
#include "tools3d/Mesh.h"
#include "tools3d/Common.h"
#include "Singleton.h"
#include <utility>

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

		private:
			MeshManager() = default;
			VboId m_staticGeometry;
			std::vector<Vertex> m_verticesStaticGeometry;
			std::vector<u32> m_indicesStaticGeometry;
			bool m_canAddStaticGeometry = false;
		};

	}
}

