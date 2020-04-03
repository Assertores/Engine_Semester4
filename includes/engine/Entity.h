#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <list>
#include <string>
#include <cassert>

//===== ===== Intern ===== =====
#include "helper/Types.h"
#include "components/Component.h"

/*!
 * the Entity in the game, holding all the diferent Components and propergates Updates etc.
 */
class Entity final
{
	friend class Scene;
	friend class GameInstance;

	static u64 ActiveEntities;

public:

	/*!
	 * @brief			creates a new Entity
	 * @param parent	the parent object in the scene graph
	 * @remarks			if nullptr the Entity will be automaticly a virtual Entity
	 */
	Entity(Entity* parent);

	/*!
	 * @brief	adds component to component list if it dosnt already exist
	 * @tparam T	the Component type to add
	 * @remarks		must inherent from Component
	 * @return	the component
	 * @remarks	null if askt for transform but Entity is Virtual
	 */
	template<typename T>
	T* AddComponent(void) {
		if(T::TypeID == INVALID_COMPONENT_ID)
			Component::RegisterComponentType<T>();

		if(isVirtual && T::TypeID <= 0)//0 is Transform
			return nullptr;

		else if(HasComponent<T>())
			return GetComponent<T>();

		if(T::TypeID >= components.size())
			components.resize(T::TypeID + 1);

		components[T::TypeID] = new T;
		components[T::TypeID]->dad = this;
		components[T::TypeID]->OnCreate();

		return GetComponent<T>();
	}

	/*!
	 * @brief	removes the component from the component list
	 * @tparam T	the Component type to remove
	 * @remarks		must inherent from Component
	 */
	template<typename T>
	void RemoveComponent(void) {
		if(!HasComponent<T>() || T::TypeID <= 0)//0 is Transform. Transform cand be Removed
			return;

		this->components[T::TypeID].OnDestroy();
		delete(this->components[T::TypeID]);//TODO: change to save delete makro
		this->components[T::TypeID] = nullptr;
	}

	/*!
	 * @brief			changes the parent Entity
	 * @param parent	new parent
	 * @return			if change was sucsessfull
	 */
	bool AttachTo(Entity* parent);

	/*!
	 * @brief			changes the parent Entity to nullptr
	 */
	void Detatch(void);

	//! @cond
	//! obsolete
	Entity* FindChildEntity(Entity* parent);
	//! @endcond

	/*!
	 * @return	chlidens list
	 */
	const std::list<Entity*> GetChildren(void);

	/*!
	 * @tparam T	the Component type to get
	 * @remarks		must inherent from Component
	 * @return	a pointer to the component atached to the Entity
	 */
	template <typename T>
	T* GetComponent(void) {
		return reinterpret_cast<T*>(this->components[T::TypeID]);
	}

	/*!
	 * @tparam T	the Component type in question
	 * @remarks		must inherent from Component
	 * @return	wather a given component is already atached to the Entity
	 */
	template<typename T>
	bool HasComponent(void) {
		if(T::TypeID < 0 || T::TypeID >= components.size())
			return false;

		return this->components[T::TypeID] != nullptr;
	}

	std::string name;

protected:

	/*!
	 * @brief	calls all creates in components
	 */
	void Create(void);

	/*!
	 * @brief	calls all updates in cildren and components
	 */
	void Update(float deltaTime);

	/*!
	 * @brief	calls all destroy in cildren and components
	 */
	void Destroy(void);

private:

	/*!
	 * @brief	use this for the rood object
	 */
	Entity();

	u64 entityID = 0;
	Entity* parent = nullptr;
	std::list<Entity*> children;
	std::vector<Component*> components;
	bool isVirtual;
};
