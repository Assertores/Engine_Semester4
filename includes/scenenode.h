#include "helper/Matrix4x4.h"
#include "components/Transform.h"

class SceneNode {
	bool dirty = true;
	Matrix4x4 worldMatrix;
	
	//entity
	int entityID = -1;

	SceneNode* parent = nullptr;
	SceneNode* prev = nullptr;
	SceneNode* next = nullptr;

	ToWorldSpace() {

	}

	ToLocalSpace() {

	}

	//chiled will alway be added as first child of parent so parent == previous
	void AttachTo(SceneNode* parent) {
		//TODO: set all variables

		MakeFreeFloating();

		this->parent = prev;

		this->prev = prev;
		this->next = prev->next;

		this->next->prev = this;
		this->prev->next = this;

		DoUpdateWithoutCheck();
	}

	void Delete() {
		MakeFreeFloating();

		//TODO: call pool alocator;
	}

	void UpdateTransforms() {
		if (!parent->dirty /*TODO: && local transform not dirty*/) return;

		DoUpdateWithoutCheck();
	}

	const Matrix4x4 GetWorldMatrix(void) const {
		return worldMatrix;
	}

	//TODO:
	//TODO: 
	//TODO: bounding volumen hyrachie

	//private
	void MakeFreeFloating() {
		if (nullptr != this->prev) this->prev->next = this->next;
		if (nullptr != this->next) this->next->prev = this->prev;

		this->prev = nullptr;
		this->next = nullptr;
		this->parent = nullptr;
	}

	void DoUpdateWithoutCheck() inline {
		//TODO: find you transform
		this->worldMatrix = parent->worldMatrix * Matrix4x4::Identity; //TODO: add local matrix here
		this->dirty = true;
	}
};

//-logic-
//update world space matrix
//reparent all elements
//if(at least one element snaps)
//	snap all elements
//	update world space matrix
//[-physic-]
//[-netcode-]
//-render-

struct trans {
	Vector3 pos;
	Quaternion rot;
	Vector3 scale;
};
