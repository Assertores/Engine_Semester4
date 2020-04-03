#pragma once

//===== ===== Extern ===== =====
#include <d3d11.h>

//===== ===== Intern ===== =====
#include "Component.h"

/*!
 * can be used to give Entitys diferent Shading
 */
class Material : public Component {
public:
	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;
};
