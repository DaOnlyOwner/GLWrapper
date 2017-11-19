#pragma once

#include "glad/glad.h"
#include "Common.h"
#include <stdexcept>
#include <vector>
#include <cassert>

namespace doo
{
	namespace gl
	{

		MAKE_EXCEPTION(ShaderLinkerError);
		MAKE_EXCEPTION(ShaderCompileError);
		MAKE_EXCEPTION(LayoutParseError);

		struct VboId
		{
			ObjId Vbo;
			ObjId Vao;
			ObjId Ebo;
		};

		struct ShaderSrcCode
		{
			std::string Code;
			GLenum Type;
		};

		struct VertexLayoutInfo
		{
			u32 NumComponents;
			u32 Stride = 1;
			u32 Offset;
			GLenum Type;
			GLboolean Normalized = 0;
		};


		struct InterleavedLayout
		{
			InterleavedLayout(u32 p_vertexDeclLength) : m_vertexDeclLength(p_vertexDeclLength)
			{
			}

			const VertexLayoutInfo* GetInterleavedLayoutInfo() const
			{
				return decls;
			}

			u32 GetNumAttribPtrs() const
			{
				return m_numAttribPtrs;
			}

			InterleavedLayout &
				Add(u32 p_numComponents, GLenum p_type = GL_FLOAT, bool p_normalized = false)
			{
				assert(m_numAttribPtrs < 7);
				decls[m_numAttribPtrs].Type = p_type;
				decls[m_numAttribPtrs].Normalized = p_normalized;
				decls[m_numAttribPtrs].NumComponents = p_numComponents;
				decls[m_numAttribPtrs].Offset = m_offset;
				decls[m_numAttribPtrs].Stride = m_vertexDeclLength;
				return *this;
			}

		private:
			VertexLayoutInfo decls[7];
			u32 m_numAttribPtrs = 0;
			u32 m_offset = 0;
			u32 m_vertexDeclLength;
		};

		ObjId CreateProgram(ShaderSrcCode* p_code, u32 p_amount);
		VboId CreateStaticVBO(void* p_vertices, u32 p_vertSize, void* p_indices, u32 p_indexSize, const InterleavedLayout& p_layout);


		
		VboId CreateVBO(void* p_vertices, u32 p_vertSize, void* p_indices, u32 p_indexSize, const VertexLayoutInfo* p_layout, u32 p_amount, GLenum
		                         p_accessModifier = GL_STATIC_DRAW);

		template<typename TVerts>
		VboId CreateStaticVBO(std::vector<TVerts> p_verts, std::vector<u32> p_indices, const InterleavedLayout& p_layout)
		{
			return CreateStaticVBO(p_verts.data(), p_verts.data(), p_indices.data(), p_indices.size(), p_layout);
		}

	}
}
