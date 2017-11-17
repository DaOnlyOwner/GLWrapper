#pragma once
#include "glad/glad.h"


// What namespace?

typedef GLbyte s8;
typedef GLshort s16;
typedef GLint s32;

typedef GLubyte u8;
typedef GLushort u16;
typedef GLuint u32;
typedef GLintptr ptr;
typedef GLuint ObjId;

typedef GLfloat f32;
typedef GLdouble f64;

/*enum class VariableTypes : GLenum
{
	Int = GL_INT,
	Float = GL_FLOAT,
	UInt = GL_UNSIGNED_INT,
	Double = GL_DOUBLE,
	UByte = GL_UNSIGNED_BYTE,
	Byte = GL_BYTE,
	Short = GL_SHORT,
	UShort = GL_UNSIGNED_SHORT
};*/

struct VertexLayoutInfo
{
	u32 NumComponents;
	u32 Stride = 1;
	u32 Offset;
	GLenum Type;
	GLboolean Normalized = 0;
};

struct Vec2
{
	f32 x, y;
};

struct Vec3
{
	f32 x, y, z;
};

struct Vec4
{
	f32 x, y, z, v;
};


#define MAKE_EXCEPTION(name) struct name : std::logic_error {explicit name(const std::string& arg) :logic_error(arg) {} }