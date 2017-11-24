#pragma once
#include "Common.h"

#define MAKE_ARITHMETIC_OPERATOR( op )						\
Vec<VDim> operator op (const Vec<VDim>& p_other)			\
{															\
	Vec<VDim> out;											\
	for (int i = 0; i<VDim; i++)							\
	{														\
		out.m_data[i] = p_other.m_data[i] op m_data[i];		\
	}														\
	return out;												\
}												



#define MAKE_ASSIGNMENT_OPERATOR( assign_op )\
Vec<VDim>& operator assign_op (const Vec<VDim>& p_other)\
{\
	for (int i = 0; i<VDim; i++)\
	{\
		m_data[i] assign_op p_other.m_data[i];\
	}\
	return *this;\
}

#define MAKE_ARITHMETIC_OPERATOR_SCALAR( op )\
Vec<VDim> operator op (f32 p_scalar)\
{\
	Vec<VDim> out;\
	for (int i = 0; i<VDim; i++)\
	{\
		out.m_data[i] = out.m_data[i] op p_scalar;\
	}\
	return out;\
}

#define MAKE_ASSIGNMENT_OPERATOR_SCALAR( assign_op )\
Vec<VDim>& operator assign_op (f32 p_scalar)\
{\
	for (int i = 0; i<VDim; i++)\
	{\
		m_data[i] assign_op p_scalar;\
	}\
	return *this;\
}



namespace doo
{
	namespace math
	{
		template<u32 VDim>
		class Vec
		{
		public:
			static_assert(VDim > 2, "Vector dimension needs to be greater than 2.");

			Vec() = default;

			Vec(float x, float y, float z, float w) : m_data{x,y,z,w}
			{
				static_assert(VDim > 3, "Dimension of vector must be greater than 3");
			}

			Vec(float x, float y, float z) : m_data{x,y,z}
			{
				static_assert(VDim > 2, "Dimension of vector must be greater than 2");
			}

			Vec(float x, float y) : m_data{x,y}
			{}

			f32 X() const { return m_data[0]; }
			f32 Y() const { return m_data[1]; }

			f32 Z() const { static_assert(VDim > 2, "Vector has not the proper dimension to access Z()"); return m_data[2]; }

			f32 W() const { static_assert(VDim > 3, "Vector has not the proper dimension to access W()"); return m_data[3]; }


			void X(u32 p_x) { m_data[0] = p_x; }
			void Y(u32 p_y) { m_data[1] = p_y; }

			void Z(f32 p_z) { static_assert(VDim > 3, "Vector has not the proper dimension to assign a Z value"); m_data[2] = p_z; }

			void W(u32 p_u) { static_assert(VDim > 3, "Vector has not the proper dimension to assign a W value"); m_data[3] = p_u; } 

			const f32* ConstData() { return m_data; } const
			f32* Data() { return m_data; }


			f32& operator[] (u32 p_index) 
			{
				return m_data[p_index];
			}

			// --- Arithmetics

			MAKE_ARITHMETIC_OPERATOR(+);
			MAKE_ARITHMETIC_OPERATOR(*);
			MAKE_ARITHMETIC_OPERATOR(-);
			MAKE_ARITHMETIC_OPERATOR(/ );

			MAKE_ARITHMETIC_OPERATOR_SCALAR(*);
			MAKE_ARITHMETIC_OPERATOR_SCALAR(/);

			MAKE_ASSIGNMENT_OPERATOR(+=);
			MAKE_ASSIGNMENT_OPERATOR(*=);
			MAKE_ASSIGNMENT_OPERATOR(-=);
			MAKE_ASSIGNMENT_OPERATOR(/= );

			MAKE_ASSIGNMENT_OPERATOR_SCALAR(/= );
			MAKE_ASSIGNMENT_OPERATOR_SCALAR(*= );


			
			f32 operator& (const Vec<VDim>& p_other)
			{
				f32 out =0;
				for(int i = 0; i<VDim; i++)
				{
					out += p_other.m_data[i] * m_data[i];
				}

				return out;
			}

			template<typename = typename std::enable_if< (VDim == 3) >::type>
			Vec<VDim> operator % (const Vec<VDim>& p_other) const
			{
				f32 x = Y() * p_other.Z() - Z() * p_other.Y();
				f32 y = Z() * p_other.X() - X() * p_other.Z();
				f32 z = X() * p_other.Y() - Y() * p_other.X();

				return { x, y, z };
			}

			f32 LengthSquared() const
			{
				f32 out = 0;
				for(int i = 0; i<VDim; i++)
				{
					out += m_data[i] * m_data[i];
				}

				return out;
			}

			f32 Length() const
			{
				return sqrt(LengthSquared());
			}

			f32 Distance(const Vec<VDim>& p_other) const
			{
				return this->operator-(p_other).Length();
			}

			f32 DistanceSquared(const Vec<VDim>& p_other) const
			{
				return this->operator-(p_other).LengthSquared();
			}

		private:
			f32 m_data[VDim];
		};

		typedef Vec<2> Vec2;
		typedef Vec<3> Vec3;
		typedef Vec<4> Vec4;
	}
}
