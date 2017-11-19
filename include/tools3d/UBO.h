#pragma once

#include "Common.h"

ObjId CreateUBO(const void* p_data, u32 p_dataSize, GLenum p_accessModifiers);

/* Padding rules:
Vec4 (16 byte size) (16 byte alignment)
Vec3 (12 byte size) (16 byte alignment)
Vec2 (8 byte size) (8 byte alignment)
float (4 byte size) (4 byte alignment)

This is not ready yet, but it allows to check for the correct alignment of a std140 layout ubo. Works like this:

typedef CheckStd140<Std140Type::Vec3,Std140Type::Float, Std140Type::Float> check; <- arguments have to applied in the reverse order (this might change at some point). Won't compile here. Vec3 needs to be aligned correctly.
typedef CheckStd140<Std140Type::Vec3,Std140Type::Float, Std140Type::Float, Std140Type::Float, Std140Type::Float> check; <- this will compile, vec3 is correctly aligned.
*/

#ifndef NDEBUG

enum class Std140Type
{
	Float,  
	Vec2,
	Vec3,
	Vec4

	// Okay for now
};

template <Std140Type... VTypes>
struct CheckStd140
{
    enum {offset =0,
          offsetPrevious = 0,
         };
};


template <Std140Type... VTypes>
struct CheckStd140<Std140Type::Float, VTypes...>
{
    enum { offsetPrevious = CheckStd140<VTypes...>::offset,
           offset = offsetPrevious + 4};
    static_assert(offsetPrevious % 4 == 0, "The previous member has to be padded to be aligned to a 4 byte boundary. Float has an alignment of 4 byte");
};


template <Std140Type... VTypes>
struct CheckStd140<Std140Type::Vec2, VTypes...>
{
    enum { offsetPrevious = CheckStd140<VTypes...>::offset,
           offset = offsetPrevious + 8};
    static_assert(offsetPrevious % 8 == 0, "The previous member has to be padded to be aligned to a 8 byte boundary. Vec2 has an alignment of 8 byte.");
};


template <Std140Type... VTypes>
struct CheckStd140<Std140Type::Vec3, VTypes...>
{
    enum { offsetPrevious = CheckStd140<VTypes...>::offset,
           offset = offsetPrevious + 12};
    static_assert(offsetPrevious % 16 == 0, "The previous member has to be padded to be aligned to a 16 byte boundary. A Vec3 has an alignment of 16 byte!");
};


template <Std140Type... VTypes>
struct CheckStd140<Std140Type::Vec4, VTypes...>
{
    enum { offsetPrevious = CheckStd140<VTypes...>::offset,
           offset = offsetPrevious + 16};
    static_assert(offsetPrevious % 16 == 0, "The previous member has to be padded to be aligned to a 16 byte boundary. Vec4 has an alignment of 16 byte.");
};

#endif