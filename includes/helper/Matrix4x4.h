#pragma once

//===== ===== Intern ===== =====
#include "helper/Vector3.h"
#include "helper/Quaternion.h"

#define M_PI 3.14159265358979f

#define ANG_TO_RAD (M_PI / 180.0f)

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

	inline static Matrix4x4 FromView(const Vector3& pos) {
		return Matrix4x4{
			1.0f, 0.0f, 0.0f, -Vector3::UnitX.Dot(pos),
			0.0f, 1.0f, 0.0f, -Vector3::UnitY.Dot(pos),
			0.0f, 0.0f, -1.0f, -Vector3::UnitZ.Dot(pos),
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

	inline static Matrix4x4 FromPerspetiveFOV(float fov, float aspect, float nearPlane, float farPlane) {
		float scaleY = 1.0f / tan(ANG_TO_RAD * fov * 0.5f);
		float scaleX = scaleY / aspect;

		return Matrix4x4{
			scaleX, 0.0f, 0.0f, 0.0f,
			0.0f, scaleY, 0.0f, 0.0f,
			0.0f, 0.0f, -farPlane / (farPlane - nearPlane), -farPlane * nearPlane / (farPlane - nearPlane),
			0.0f, 0.0f, -1.0f, 0.0f,
		};
	}

	inline static Matrix4x4 FromTranslation(const Vector3& pos) {
		Matrix4x4 m = Matrix4x4::Identity;

		m.m14 = pos.x;
		m.m24 = pos.y;
		m.m34 = pos.z;

		return m;
	}

	inline static Matrix4x4 FromScale(const Vector3& scale) {
		Matrix4x4 m = Matrix4x4::Identity;

		m.m11 = scale.x;
		m.m22 = scale.y;
		m.m33 = scale.z;

		return m;
	}

	inline static Matrix4x4 FromRotation(const Quaternion& orientation) {
		Matrix4x4 Result = Matrix4x4::Identity;

		float fTx = orientation.x + orientation.x;
		float fTy = orientation.y + orientation.y;
		float fTz = orientation.z + orientation.z;
		float fTwx = fTx * orientation.w;
		float fTwy = fTy * orientation.w;
		float fTwz = fTz * orientation.w;

		float fTxx = fTx * orientation.x;
		float fTxy = fTy * orientation.x;
		float fTxz = fTz * orientation.x;

		float fTyy = fTy * orientation.y;
		float fTyz = fTz * orientation.y;

		float fTzz = fTz * orientation.z;

		Result.m11 = 1.0f - (fTyy + fTzz);
		Result.m12 = fTxy - fTwz;
		Result.m13 = fTxz + fTwy;

		Result.m21 = fTxy + fTwz;
		Result.m22 = 1.0f - (fTxx + fTzz);
		Result.m23 = fTyz - fTwx;

		Result.m31 = fTxz - fTwy;
		Result.m32 = fTyz + fTwx;
		Result.m33 = 1.0f - (fTxx + fTyy);

		return Result;
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
