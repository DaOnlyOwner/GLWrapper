#pragma once
#include "glad/glad.h"
#define MAKE_EXCEPTION(name) struct name : std::logic_error {explicit name(const std::string& arg) :logic_error(arg) {} }


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


