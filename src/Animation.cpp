#include "components/Animation.h"

#include "engine/Entity.h"
#include "components/Transform.h"
#include "helper/Vector3.h"

void Animation::OnUpdate(float deltaTime) {
	elapsedTime += deltaTime;

	if(myTransform == nullptr) {
		myTransform = GetDad()->GetComponent<Transform>();
	}

	myTransform->rotation = Quaternion::FromAngleAxis(Vector3::UnitX, elapsedTime * 1.39863425) * Quaternion::FromAngleAxis(Vector3::UnitY, elapsedTime * 0.730948235609f);

	myTransform->scale = Vector3::UnitScale * ((sin(elapsedTime) + 1.4f) / 2.0f);
}
