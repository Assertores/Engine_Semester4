#include "components/Animation.h"

#include "engine/Entity.h"
#include "components/Transform.h"
#include "helper/Vector3.h"

Animation::OnUpdate(float deltaTime) {
	gameTime += deltaTime;

	if(myTransform == nullptr) {
		myTransform = GetDad()->GetComponent<Transform>();
	}

	myTransform->rotation.z += deltaTime;

	myTransform->scale = Vector3::UnitScale * ((sin(gameTime) + 1.4f) / 2.0f);
}
