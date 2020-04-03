#include "engine/Entity.h"
#include <algorithm>

#include "components/Component.h"
#include "components/Transform.h"
#include "engine/GameInstance.h"

u64 Entity::ActiveEntities = 0;

Entity::Entity(Entity* parent) : entityID(++ActiveEntities) {

	isVirtual = (parent == nullptr || parent->isVirtual);

	if(isVirtual) {
		GameInstance::GetInstance().Add(*this);
	} else {
		AddComponent<Transform>();
		AttachTo(parent);
	}
}

Entity::Entity() : entityID(++ActiveEntities) {
	isVirtual = false;
	AddComponent<Transform>();
}

bool Entity::AttachTo(Entity* parent) {
	if(isVirtual)
		return false;
	if(parent == nullptr) {
		Detatch();
		return true;
	}
	if(parent->isVirtual)
		return false;

	if(this->entityID != parent->entityID) //&& check if parent is a child of this entity
	{
		this->Detatch();
		this->parent = parent;
		this->parent->children.push_back(this);

		return true;
	}

	return false;
}

void Entity::Detatch(void) {
	if(!this->parent)
		return;

	this->parent->children.remove(this);
	this->parent = nullptr;
}

Entity* Entity::FindChildEntity(Entity* parent) {
	for(auto& child : this->children) {
		if(child != nullptr) {
			if(parent->entityID == child->entityID)
				return child;

			if(auto ret = child->FindChildEntity(parent))
				return ret;
		}
	}

	return nullptr;
}

const std::list<Entity*> Entity::GetChildren() {
	return this->children;
}

void Entity::Create(void) {
	for(auto& it : components) {
		if(nullptr == it)
			continue;

		it->OnCreate();
	}
}

void Entity::Update(float deltaTime) {
	if(components.size() > 0) {
		for(auto& it : components) {
			if(nullptr == it)
				continue;

			it->OnUpdate(deltaTime);
		}
	}

	if(children.size() > 0)
		for(auto& it : children)
			it->Update(deltaTime);
}

void Entity::Destroy(void) {
	Detatch();

	for(auto& it : components) {
		if(nullptr == it)
			continue;

		it->OnDestroy();
		delete(it);//TODO: change to save delete makro
	}
	this->components.clear();

	for(auto& it : children) {
		it->Destroy();
		delete(it);
	}
	this->children.clear();
}
