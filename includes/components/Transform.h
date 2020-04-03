#pragma once

//===== ===== Extern ===== =====
//===== ===== Intern ===== =====
#include "Component.h"
#include "helper/Vector3.h"
#include "helper/Quaternion.h"
#include "helper/Matrix4x4.h"

/*!
 * the position, rotation and scaling of the Entity in the 3D space
 * will be automaticly added to components with in the Scene
 */
class Transform : public Component {
public:
	Transform();

	Vector3 pos = Vector3::Zero;
	Quaternion rotation = Quaternion::Zero;
	Vector3 scale = Vector3::UnitScale;

	inline Matrix4x4 GetTransformMatrix(void) const {
		return Matrix4x4::FromTranslation(this->pos) * Matrix4x4::FromRotation(rotation) * Matrix4x4::FromScale(this->scale);
	}
};
