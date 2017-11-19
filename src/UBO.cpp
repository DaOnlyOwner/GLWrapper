#include "tools3d/UBO.h"

ObjId CreateUBO(const void* p_data, u32 p_dataSize, GLenum p_accessModifiers)
{
	ObjId ubo;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, p_dataSize, p_data, p_accessModifiers);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
