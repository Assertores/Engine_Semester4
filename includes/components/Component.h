#pragma once

//===== ===== Extern ===== =====
//===== ===== Intern ===== =====

#define INVALID_COMPONENT_ID 0

//! forward declaration
class Entity;
class Transform;

static int ComponentCount = 0; //!< 0 is Reserved for Transform

/*!
 * the virtual root component to be inherented from the all
 */
class Component {
	friend Entity;
	friend Transform;

public:
	/*!
	 * @brief		dynamic component type id assignment
	 * @tparam T	the Component type to register
	 * @remarks		must inherent from Component
	 */
	template <typename T>
	static void RegisterComponentType(void) {
		if (T::TypeID != INVALID_COMPONENT_ID)
			return;

		ComponentCount++;
		T::TypeID = ComponentCount;
	}

	/*!
	 * @brief	will be called once after creation
	 */
	virtual void OnCreate(void) {};

	/*!
	 * @brief			will be called once per frame
	 * @param deltaTime	the time between the last and the current frame in seconds
	 */
	virtual void OnUpdate(float deltaTime) {};

	/*!
	 * @brief	will be called once befor destruction
	 */
	virtual void OnDestroy(void) {};


protected:

	/*!
	 * @return	the Entity the component is parented on
	 */
	Entity* GetDad(void) { return dad; };

private:
	static int TypeID;
	Entity* dad;
};
