#include "tools3d/VBO.h"
#include <string>

inline doo::ObjId compileShader(const char* p_code, GLenum p_type)
{
	GLint success;
	char log[1000];
	doo::ObjId shaderId = glCreateShader(p_type);
	glShaderSource(shaderId, 1, &p_code, nullptr);
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 1000, nullptr, log);
		throw doo::gl::ShaderCompileError("Shader didn't compile successfully:\n" + std::string(log));
	}

	return shaderId;
}

doo::ObjId doo::gl::CreateProgram(ShaderSrcCode* p_code, u32 p_amount)
{
	ObjId programOut = glCreateProgram();
	
	ObjId* savedIds = new ObjId[p_amount];

	for(u32 i = 0; i<p_amount; i++)
	{
		ObjId shaderId = compileShader(p_code[i].Code.c_str(), p_code[i].Type);
		savedIds[i] = shaderId;
		glAttachShader(programOut, shaderId);
	}

	glLinkProgram(programOut);
	s32 success;
	char log[1000];
	glGetProgramiv(programOut, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(programOut, 1000, nullptr, log);
		throw ShaderLinkerError("Linking of shaders failed:\n" + std::string(log));
	}

	for(u32 i = 0; i<p_amount; i++)
	{
		glDetachShader(programOut, savedIds[i]);
		glDeleteShader(savedIds[i]);
	}
	delete[] savedIds;
	return programOut;
}


doo::gl::VboId doo::gl::CreateVBO(void* p_vertices, u32 p_vertSize, void* p_indices, u32 p_indexSize, const VertexLayoutInfo* p_layout, u32 p_amount, GLenum p_accessModifier)
{
	u32 vbo;
	u32 vao;
	u32 ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, p_vertSize, p_vertices, p_accessModifier);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_indexSize, p_indices, p_accessModifier);

	for (u32 i = 0; i<p_amount; i++)
	{
		const VertexLayoutInfo& info = p_layout[i];
		glVertexAttribPointer(i, info.NumComponents, info.Type, info.Normalized, info.Stride, &info.Offset);
		glEnableVertexAttribArray(i);
	}

	// Unbind everything
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return {vbo,vao,ebo};
}
