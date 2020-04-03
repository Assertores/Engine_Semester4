#pragma once

#include <cassert>
#include <cmath>
#include <cfloat>

/*!
 * a normal vector 3 class
 */
class Vector3
{
public:
	
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3()
	{
		// Nothing to do here.
	}

	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) // <- This is called "initializer list"
	{
		// Nothing to do here.
	}

	/*!
	 * @brief	element wise addition
	 */
	inline Vector3 operator+(const Vector3& rhs)
	{
		return Vector3(
			this->x + rhs.x,
			this->y + rhs.y,
			this->z + rhs.z
		);
	}

	/*!
	 * @brief	element wise subtraction
	 */
	inline Vector3 operator-(const Vector3& rhs)
	{
		return Vector3(
			this->x - rhs.x,
			this->y - rhs.y,
			this->z - rhs.z
		);
	}

	/*!
	 * @brief	element wise scaling
	 */
	inline Vector3 operator*(const float scalar) const
	{
		return Vector3(
			this->x * scalar,
			this->y * scalar,
			this->z * scalar
		);
	}

	/*!
	 * @brief	element wise scaling division
	 */
	inline Vector3 operator/(const float scalar)
	{
		assert(scalar != 0.0f);

		return Vector3(
			this->x / scalar,
			this->y / scalar,
			this->z / scalar
		);
	}

	inline Vector3& operator+=(const Vector3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	inline Vector3& operator-=(const Vector3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	inline Vector3& operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}

	inline Vector3& operator/=(const float scalar)
	{
		assert(scalar != 0.0f);

		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;

		return *this;
	}

	inline const float Magnitude(void) const
	{
		return sqrt(SquareMagnitude());
	}

	inline const float SquareMagnitude(void) const
	{
		return (
			(this->x * this->x) +
			(this->y * this->y) +
			(this->z * this->z)
		);
	}

	inline const float Distance(const Vector3& rhs)
	{
		return ((*this) - rhs).Magnitude();
	}

	inline const float Dot(const Vector3& rhs) const
	{
		return {
			(this->x * rhs.x) +
			(this->y * rhs.y) +
			(this->z * rhs.z)
		};
	}

	inline const Vector3 Cross(const Vector3& rhs) const
	{
		return Vector3(
			(this->y * rhs.z) - (this->z * rhs.y),
			(this->z * rhs.x) - (this->x * rhs.z),
			(this->x * rhs.y) - (this->y * rhs.x)
		);
	}

	inline const bool Normalize(void)
	{
		const float magnitude = this->Magnitude();

		if (magnitude >= FLT_MIN)
		{
			float inverseMagnitude = 1.0f / magnitude;

			this->x *= inverseMagnitude;
			this->y *= inverseMagnitude;
			this->z *= inverseMagnitude;

			return true;
		}
		else
		{
			return false;
		}
	}

	inline Vector3 Lerp(Vector3& rhs, float t)
	{
		return (*this) + (rhs - (*this)) * t;
	}

	static const Vector3 UnitX;		//!< 1, 0, 0,
	static const Vector3 UnitY;		//!< 0, 1, 0,
	static const Vector3 UnitZ;		//!< 0, 0, 1,
	static const Vector3 UnitScale;	//!< 1, 1, 1,
	static const Vector3 Zero;		//!< 0, 0, 0,
};
