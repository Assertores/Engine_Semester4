#pragma once

//===== ===== Extern ===== =====
//===== ===== Intern ===== =====
#include "Component.h"
#include "helper/Vector3.h"

/*!
 * the position, rotation and scaling of the Entity in the 3D space
 * will be automaticly added to components with in the Scene
 */
class Transform : public Component {
public:
	Transform();

	Vector3 pos;
	Vector3 rotation;
	Vector3 scale;
};
