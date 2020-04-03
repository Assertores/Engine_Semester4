#include "engine/GameInstance.h"

#include <cassert>

#include "engine/Entity.h"
#include "rendering/Window.h"

GE_DEFINE_SINGLETON(GameInstance)

void GameInstance::InitGame(const Window& myWindow) {
	scenes.push_back(Scene());
	currentScene = 0;
	scenes[currentScene].Load();
	this->renderer.Initialize(myWindow, true, false);
}


void GameInstance::ChangeScene(int newScene)
{
	if(newScene < 0 || newScene >= scenes.size())
		return;

	scenes[currentScene].Unload();
	currentScene = newScene;
	scenes[currentScene].Load();
}

void GameInstance::Add(Entity& virtualEntity)
{
	virtualEntities.push_back(&virtualEntity);
}

void GameInstance::Remove(Entity& virtualEntity)
{
}

void GameInstance::UpdateCurrentScene(float deltaTime)
{
	for(auto& it : virtualEntities)
		it->Update(deltaTime);

	scenes[currentScene].Update(deltaTime);
}

void GameInstance::RenderCurrentScene(Window& target) {
	//assert(false && "not implimented");
	renderer.BeginRender();

	//render cubes
	scenes[currentScene].Render(renderer);

	renderer.EndRender();
}

void GameInstance::Shutdown(void) {
	scenes[currentScene].Unload();

	scenes.clear();
}
