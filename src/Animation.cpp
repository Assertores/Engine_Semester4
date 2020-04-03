#include "components/Animation.h"

#include "engine/Entity.h"
#include "components/Transform.h"
#include "helper/Vector3.h"

void Animation::OnUpdate(float deltaTime) {
	elapsedTime += deltaTime;

	if(myTransform == nullptr) {
		myTransform = GetDad()->GetComponent<Transform>();
	}

	myTransform->rotation += Quaternion::FromAngleAxis(Vector3::UnitX, deltaTime);
	//myTransform->rotation += Quaternion::FromAngleAxis(Vector3::UnitY, deltaTime * 0.5698045f);

	//myTransform->scale = Vector3::UnitScale * ((sin(elapsedTime) + 1.4f) / 2.0f);
}
