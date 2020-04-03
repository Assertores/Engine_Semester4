#pragma once

//===== ===== Extern ===== =====
#include <d3d11.h>

//===== ===== Intern ===== =====
#include "Component.h"

/*!
 * can be used to load diferent meshes to diferent Entitys
 */
class Mesh : public Component {
public:
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	int indexBufferCount = 0;

	ID3D11Buffer* constBuffer = nullptr;
};
