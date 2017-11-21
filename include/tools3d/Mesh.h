#pragma once
#include <vector>
#include "Common.h"

namespace doo
{
	namespace gl
	{

		struct Vertex
		{
			Vec3 Position;
			Vec3 Normal;
			//f32 Tangent[3];
			//f32 Bitangent[3];
			//f32 TextCoords[2];
		};

		class Mesh
		{
		public:
			Mesh(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices, const std::string& p_name);
			
			u32 GetIndexCount() const
			{
				return m_indexCount;
			}

			u32 GetOffsetIntoVbo() const
			{
				return m_offsetIntoVBO;
			}

			u32 GetOffsetIntoEbo() const
			{
				return m_offsetIntoEBO;
			}
			
		private:
			u32 m_indexCount;
			u32 m_offsetIntoVBO;
			u32 m_offsetIntoEBO;
			std::string m_name;
		};
	
	}
}
