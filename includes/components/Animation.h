#pragma once

//===== ===== Extern ===== =====
//===== ===== Intern ===== =====
#include "Component.h"
#include "helper/Vector3.h"

/*!
 * scales and rotates the Entity
 */
class Animation : public Component {
private:
	float gameTime = 0.0f;
	Transform* myTransform = nullptr;
};
