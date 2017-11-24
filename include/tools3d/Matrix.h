#pragma once
#include "Common.h"
#include "Vector.h"


#define MAKE_MATRIX_OPERATION_SCALAR( op )\
Matrix<VDim> operator op (f32 p_scalar)\
{\
	Matrix<VDim> out;\
	for (int i = 0; i<VDim; i++)\
	{\
		for (int j = 0; j<VDim; j++)\
		{\
			out[i*VDim + j] = m_data[i*VDim + j] op p_scalar;\
		}\
	}\
	return out;\
}

#define MAKE_MATRIX_OPERATION( op )\
Matrix<VDim> operator op (const Matrix<VDim>& p_other)\
{\
	Matrix<VDim> out;\
	for (int i = 0; i<VDim; i++)\
	{\
		for (int j = 0; j<VDim; j++)\
		{\
			out[i*VDim + j] = p_other.m_data[i*VDim + j] op m_data[i*VDim + j];\
		}\
	}\
	return out;\
}\


#define MAKE_MATRIX_ASSIGNMENT_OPERATION(assign_op, op)\
Matrix<VDim>& operator assign_op (const Matrix<VDim>& p_other)\
{\
	m_data = (*this op p_other).m_data;\
	return *this;\
}

namespace doo
{
	namespace math
	{
		// I will only support n,n matrices
		template <u32 VDim>
		class Matrix
		{

		public:


			MAKE_MATRIX_OPERATION_SCALAR(+);
			MAKE_MATRIX_OPERATION_SCALAR(*);
			MAKE_MATRIX_OPERATION_SCALAR(/);
			MAKE_MATRIX_OPERATION_SCALAR(-);

			MAKE_MATRIX_OPERATION(+);
			MAKE_MATRIX_OPERATION(-);

			Vec<VDim> operator* (const Vec<VDim>& p_other)
			{
				Vec<VDim> out;
				for (int i = 0; i<VDim; i++)
				{
					f32 result = 0;
					for(int k = 0; k<VDim; k++)
					{
						result += m_data[i*VDim + k] * p_other[k];
					}

					out[i] = result;
				}

				return out;
			}
			Matrix<VDim> operator* (const Matrix<VDim>& p_other)
			{
				Matrix<VDim> out;
				for(int i = 0; i<VDim; i++)
				{
					for(int j = 0; j<VDim; j++)
					{
						f32 result = 0;

						for(int k = 0; k<VDim; k++)
						{
							result += m_data[k*VDim + j] * p_other.m_data[i * VDim + k];
						}

						out.m_data[i * VDim + j] = result;
					}
				}

				return out;
			}

			MAKE_MATRIX_ASSIGNMENT_OPERATION(+=, +);
			MAKE_MATRIX_ASSIGNMENT_OPERATION(*=, *);
			


		private:
			f32 m_data[VDim * VDim];
		};
	}
}