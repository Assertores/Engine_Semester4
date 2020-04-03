#pragma once
//===== ===== Extern ===== =====
#include <cassert>
#include <cmath>
//===== ===== Intern ===== =====
#include "helper/Vector3.h"

/*!
 * a normal quaternion class
 */
class Quaternion
{
public:

	float w = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Quaternion()
	{
		// Nothing to do here.
	}

	Quaternion(float _w, float _x, float _y, float _z)
		: w(_w), x(_x), y(_y), z(_z) //!< This is called "initializer list"
	{
		// Nothing to do here.
	}

	/*!
	 * @brief	element wise addition
	 */
	inline Quaternion operator+(const Quaternion& rhs)
	{
		return Quaternion(
			this->w + rhs.w,
			this->x + rhs.x,
			this->y + rhs.y,
			this->z + rhs.z
		);
	}

	/*!
	 * @brief	element wise subtraction
	 */
	inline Quaternion operator-(const Quaternion& rhs)
	{
		return Quaternion(
			this->w - rhs.w,
			this->x - rhs.x,
			this->y - rhs.y,
			this->z - rhs.z
		);
	}

	/*!
	 * @brief	element wise scaling
	 */
	inline Quaternion operator*(const float scalar)
	{
		return Quaternion(
			this->w * scalar,
			this->x * scalar,
			this->y * scalar,
			this->z * scalar
		);
	}

	inline Quaternion operator*(const Quaternion& lhs)
	{
		return Quaternion(
			this->w * lhs.w - this->x * lhs.x - this->y * lhs.y - this->z * lhs.z,
			this->w * lhs.x + this->x * lhs.w + this->y * lhs.z - this->z * lhs.y,
			this->w * lhs.y + this->y * lhs.w + this->z * lhs.x - this->x * lhs.z,
			this->w * lhs.z + this->z * lhs.w + this->x * lhs.y - this->y * lhs.x
		);
	}

	/*!
	 * @brief	element wise scaling division
	 */
	inline Quaternion operator/(const float scalar)
	{
		assert(scalar != 0.0f);

		return Quaternion(
			this->w / scalar,
			this->x / scalar,
			this->y / scalar,
			this->z / scalar
		);
	}

	inline Quaternion& operator+=(const Quaternion& rhs)
	{
		this->w += rhs.w;
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	inline Quaternion& operator-=(const Quaternion& rhs)
	{
		this->w -= rhs.w;
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	inline Quaternion& operator*=(const float scalar)
	{
		this->w *= scalar;
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}

	inline Quaternion& operator/=(const float scalar)
	{
		assert(scalar != 0.0f);

		this->w /= scalar;
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;

		return *this;
	}

	static Quaternion FromAngleAxis(const Vector3& axis, float angle) {
		float fHalfAngle(0.5f * angle);
		float fSin = sin(fHalfAngle);

		Quaternion result;

		result.w = cos(fHalfAngle);
		result.x = fSin * axis.x;
		result.y = fSin * axis.y;
		result.z = fSin * axis.z;

		return result;
	}

	static Quaternion Zero;
};
