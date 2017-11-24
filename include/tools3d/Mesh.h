#pragma once
#include <vector>
#include "Common.h"
#include "Vector.h"

namespace doo
{
	namespace gl
	{
		struct Vertex
		{
			math::Vec3 Position;
			math::Vec3 Normal;
			//f32 Tangent[3];
			//f32 Bitangent[3];
			//f32 TextCoords[2];
		};

		class Mesh
		{
		public:
			Mesh() = default;
			Mesh(const std::vector<Vertex>& p_vertices, const std::vector<u32>& p_indices, const std::string& p_name, bool p_isStatic);
			
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

			const std::string& GetName() const
			{
				return m_name;
			}

			bool IsStatic() const
			{
				return m_isStatic;
			}

			static void BeginStaticGeometry();
			static void EndStaticGeometry();
			
		private:
			bool m_isStatic = true;
			u32 m_indexCount;
			u32 m_offsetIntoVBO;
			u32 m_offsetIntoEBO;
			std::string m_name;



		};
	
	}
}
