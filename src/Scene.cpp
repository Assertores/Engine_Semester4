#include "engine/Scene.h"

#include "components/Transform.h"
#include "components/Animation.h"
#include "components/Mesh.h"

void Scene::Load() {
	root = new Entity();
	auto sunEntity = new Entity(root);

	root->AddComponent<Animation>();

	sunEntity->AddComponent<Animation>();
	sunEntity->AddComponent<Mesh>();

	auto planetEntity = new Entity(sunEntity);
	planetEntity->AddComponent<Mesh>();

	auto planetTransform = planetEntity->GetComponent<Transform>();
	planetTransform->pos.x = 2;

	auto camera = new Entity(root);
	auto cameraTransform = camera->GetComponent<Transform>();

	cameraTransform->pos.z = -5;

	SetMainCamera(camera);
}

void Scene::Update(float deltaTime) {
	root->Update(deltaTime);
}

void Scene::Render(const Renderer& renderer) {
	assert(root->HasComponent<Transform>());
	renderer.RenderQuad(*root->GetComponent<Transform>());
}

void Scene::Unload() {
	root->Destroy();
	delete(root);
	root = nullptr;
}

void Scene::SetMainCamera(Entity* newCamera) {
	this->mainCamera = newCamera;
}
