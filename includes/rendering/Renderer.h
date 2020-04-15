#pragma once

//===== ===== Extern ===== =====
#include <dxgi.h>
#include <d3d11.h>

//===== ===== Intern ===== =====
#include "Window.h"
#include "components/Transform.h"

class Mesh;
class Material;

class Renderer {
public:

	/*!
	 * @brief	inits all values and sets up flags, values and buffers in Graphics API
	 */
	bool Initialize(const Window& myWindow, bool enalbeVSync, bool enableFullscreen);

	/*!
	 * @brief	celan up
	 */
	void ShutDown(void);

	/*!
	 * @brief	screen clear from last frame
	 */
	void BeginRender(void) const;

	/*!
	 * @brief	presents finished image to screen
	 */
	void EndRender(void) const;

	/*!
	 * @brief			instructs GPU to draw a Quad to the screen
	 * @param transform	the transform of the quad
	 */
	void RenderQuad(const Transform& transform) const;

	/*!
	 * @brief		instructs GPU to draw a mesh to the screen
	 * @param mesh	vertex and index buffer to to render
	 * @param mat	vertex and pixel shader to use
	 * @remars		will use standard shading if left to nullptr
	 */
	void RenderMesh(Mesh& mesh, Material* mat = nullptr) const;

private:

	/*!
	 * @brief	creats vertex and index buffer for a Quad
	 */
	bool CreateBuffer(void);

	/*!
	 * @brief	creats standard vertex and pixel shader
	 */
	bool CreateShader(void);

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChan = nullptr;
	ID3D11RenderTargetView* renderTargetView = nullptr;
	ID3D11Texture2D* depthStencilBuffer = nullptr;
	ID3D11DepthStencilState* depthStencilState = nullptr;
	ID3D11DepthStencilView* depthStencilView = nullptr;
	ID3D11RasterizerState* rasterState = nullptr;

	ID3D11VertexShader* vertexShader = nullptr;
	ID3D11PixelShader* pixelShader = nullptr;
	ID3D11InputLayout* inputLayout = nullptr;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	int indexBufferCount;

	ID3D11Buffer* cameraConstBuffer;
	ID3D11Buffer* modelConstBuffer;

	int vRAM;
	char* vDesc;

	bool isVSync;
};