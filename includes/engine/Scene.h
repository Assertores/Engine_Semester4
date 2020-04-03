#pragma once

//===== ===== Extern ===== =====
//===== ===== Intern ===== =====
#include "Entity.h"

/*!
 * manages the scene graph
 */
class Scene final {
public:
	/*!
	 * @brief	initialice all entitys and component in scene (fake would be loaded from file).
	 *			call Create() funktion of root element.
	 */
	void Load();

	/*!
	 * @brief			starts recursive Update() call in root entity
	 * @param deltaTime	the time between last and current frame in seconds
	 */
	void Update(float deltaTime);

	/*!
	 * @brief	calls recursive Destroy() funktion of root element.
	 */
	void Unload();

	/*!
	 * @brief			saves \link newCamera \endlink to mainCamera
	 * @param newCamera	the entity that should be used as camera
	 */
	void SetMainCamera(Entity* newCamera);

private:
	Entity* root;

	Entity* mainCamera;
};