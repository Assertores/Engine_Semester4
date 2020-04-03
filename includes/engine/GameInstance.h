#pragma once

//===== ===== Extern ===== =====
#include <vector>

//===== ===== Intern ===== =====
#include "Scene.h"
#include "helper/Singleton.h"
#include "rendering/Renderer.h"

//! forward declaration
class Entity;

/*!
 * the game it selfe
 */
class GameInstance final {
	GE_DECLARE_SINGLETON(GameInstance);

public:

	void InitGame(const Window& myWindow);

	/*!
	 * @brief			unload old scene, change currentScene to \link newScene \endlink , load new scene
	 * @param newScene	the new Scene to be loaded
	 */
	void ChangeScene(int newScene);

	/*!
	 * @brief				adds the \link virtualEntity \endlink to the virtualEntities array
	 * @param virtualEntity	the Entity to be added
	 */
	void Add(Entity& virtualEntity);

	/*!
	 * @brief				removes the \link virtualEntity \endlink to the virtualEntities array
	 * @param virtualEntity	the Entity to be removed
	 */
	void Remove(Entity& virtualEntity);

	/*!
	 * @brief			updates the current scene and all virtual Entities
	 * @param deltaTime	the time between last frame and current frame in seconds
	 */
	void UpdateCurrentScene(float deltaTime);

	/*!
	 * @brief			renders current scene to \link target \endlink
	 * @param target	the window the scene should be rendert to
	 */
	void RenderCurrentScene(class Window& target);

	/*!
	 * @brief	cleanup
	 */
	void Shutdown(void);

private:

	std::vector<Scene> scenes;
	int currentScene;
	Renderer renderer;

	std::vector<Entity*> virtualEntities;
};