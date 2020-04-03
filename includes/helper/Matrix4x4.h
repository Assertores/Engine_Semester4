#pragma once

struct Matrix4x4
{
	float m11 = 0.0f, m12 = 0.0f, m13 = 0.0f, m14 = 0.0f;
	float m21 = 0.0f, m22 = 0.0f, m23 = 0.0f, m24 = 0.0f;
	float m31 = 0.0f, m32 = 0.0f, m33 = 0.0f, m34 = 0.0f;
	float m41 = 0.0f, m42 = 0.0f, m43 = 0.0f, m44 = 0.0f;

	Matrix4x4()
	{
		// Nothing to do here.
	}

	Matrix4x4(
		float _m11, float _m12, float _m13, float _m14,
		float _m21, float _m22, float _m23, float _m24,
		float _m31, float _m32, float _m33, float _m34,
		float _m41, float _m42, float _m43, float _m44) :
		
		m11(_m11), m12(_m12), m13(_m13), m14(_m14),
		m21(_m21), m22(_m22), m23(_m23), m24(_m24),
		m31(_m31), m32(_m32), m33(_m33), m34(_m34),
		m41(_m41), m42(_m42), m43(_m43), m44(_m44)
	{
		// Nothing to do here.
	}

	/*!
	 * @brief	element wise addition
	 */
	inline Matrix4x4 operator+(const Matrix4x4& rhs)
	{
		return Matrix4x4{
			this->m11 + rhs.m11, this->m12 + rhs.m12, this->m13 + rhs.m13, this->m14 + rhs.m14,
			this->m21 + rhs.m21, this->m22 + rhs.m22, this->m23 + rhs.m23, this->m24 + rhs.m24,
			this->m31 + rhs.m31, this->m32 + rhs.m32, this->m33 + rhs.m33, this->m34 + rhs.m34,
			this->m41 + rhs.m41, this->m42 + rhs.m42, this->m43 + rhs.m43, this->m44 + rhs.m44
		};
	}

	/*!
	 * @brief	element wise subtraction
	 */
	inline Matrix4x4 operator-(const Matrix4x4& rhs)
	{
		return Matrix4x4{
			this->m11 - rhs.m11, this->m12 - rhs.m12, this->m13 - rhs.m13, this->m14 - rhs.m14,
			this->m21 - rhs.m21, this->m22 - rhs.m22, this->m23 - rhs.m23, this->m24 - rhs.m24,
			this->m31 - rhs.m31, this->m32 - rhs.m32, this->m33 - rhs.m33, this->m34 - rhs.m34,
			this->m41 - rhs.m41, this->m42 - rhs.m42, this->m43 - rhs.m43, this->m44 - rhs.m44
		};
	}

	/*!
	 * @brief	matrix multiplication
	 */
	inline Matrix4x4 operator*(const Matrix4x4& rhs)
	{
		return Matrix4x4{
			this->m11 * rhs.m11 + this->m12 * rhs.m21 + this->m13 * rhs.m31 + this->m14 * rhs.m41,
			this->m11 * rhs.m12 + this->m12 * rhs.m22 + this->m13 * rhs.m32 + this->m14 * rhs.m42,
			this->m11 * rhs.m13 + this->m12 * rhs.m23 + this->m13 * rhs.m33 + this->m14 * rhs.m43,
			this->m11 * rhs.m14 + this->m12 * rhs.m24 + this->m13 * rhs.m34 + this->m14 * rhs.m44,

			this->m21 * rhs.m11 + this->m22 * rhs.m21 + this->m23 * rhs.m31 + this->m24 * rhs.m41,
			this->m21 * rhs.m12 + this->m22 * rhs.m22 + this->m23 * rhs.m32 + this->m24 * rhs.m42,
			this->m21 * rhs.m13 + this->m22 * rhs.m23 + this->m23 * rhs.m33 + this->m24 * rhs.m43,
			this->m21 * rhs.m14 + this->m22 * rhs.m24 + this->m23 * rhs.m34 + this->m24 * rhs.m44,

			this->m31 * rhs.m11 + this->m32 * rhs.m21 + this->m33 * rhs.m31 + this->m34 * rhs.m41,
			this->m31 * rhs.m12 + this->m32 * rhs.m22 + this->m33 * rhs.m32 + this->m34 * rhs.m42,
			this->m31 * rhs.m13 + this->m32 * rhs.m23 + this->m33 * rhs.m33 + this->m34 * rhs.m43,
			this->m31 * rhs.m14 + this->m32 * rhs.m24 + this->m33 * rhs.m34 + this->m34 * rhs.m44,

			this->m41 * rhs.m11 + this->m42 * rhs.m21 + this->m43 * rhs.m31 + this->m44 * rhs.m41,
			this->m41 * rhs.m12 + this->m42 * rhs.m22 + this->m43 * rhs.m32 + this->m44 * rhs.m42,
			this->m41 * rhs.m13 + this->m42 * rhs.m23 + this->m43 * rhs.m33 + this->m44 * rhs.m43,
			this->m41 * rhs.m14 + this->m42 * rhs.m24 + this->m43 * rhs.m34 + this->m44 * rhs.m44
		};
	}

	/*!
	 * @brief	element wise scaling
	 */
	inline Matrix4x4 operator*(const float scalar)
	{
		return Matrix4x4{
			this->m11 * scalar, this->m12 * scalar, this->m13 * scalar, this->m14 * scalar,
			this->m21 * scalar, this->m22 * scalar, this->m23 * scalar, this->m24 * scalar,
			this->m31 * scalar, this->m32 * scalar, this->m33 * scalar, this->m34 * scalar,
			this->m41 * scalar, this->m42 * scalar, this->m43 * scalar, this->m44 * scalar
		};
	}

	/*!
	 * @brief	switches x and y axis
	 */
	inline Matrix4x4 Transpose(void)
	{
		return Matrix4x4{
			this->m11, this->m21, this->m31, this->m41,
			this->m12, this->m22, this->m32, this->m42,
			this->m13, this->m23, this->m33, this->m43,
			this->m14, this->m24, this->m34, this->m44
		};
	}

	/*!
	 * 1, 0, 0, 0,
	 * 0, 1, 0, 0,
	 * 0, 0, 1, 0,
	 * 0, 0, 0, 1,
	 */
	static const Matrix4x4 Identity;

	/*!
	 * 0, 0, 0, 0,
	 * 0, 0, 0, 0,
	 * 0, 0, 0, 0,
	 * 0, 0, 0, 0,
	 */
	static const Matrix4x4 Zero;
};
