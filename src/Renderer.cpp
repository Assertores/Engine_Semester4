#include "rendering/Renderer.h"

#include <iostream>
#include <stdlib.h>
#include <d3dcompiler.h>

#include "helper/Utils.h"
#include "helper/Vector3.h"
#include "helper/Matrix4x4.h"
#include "components/Transform.h"
#include "components/Mesh.h"
#include "components/Material.h"

#ifdef _MSC_VER
#define ALIGN(x) __declspec(align(x))
#endif

struct Color {
	float r;
	float g;
	float b;
	float a;
};

struct VertexType {
	Vector3 position;
	Color color;
	Vector3 normal;
	struct {
		float u;
		float v;
	} uv;
};

ALIGN(16) struct CameraConstType {
	Matrix4x4 modelViewProjection;
	Vector3 camPos;
};

ALIGN(16) struct ModelConstType {
	Matrix4x4 model;
};

bool Renderer::Initialize(const Window& myWindow, bool enalbeVSync, bool enableFullscreen) {
	IDXGIFactory1* graphicsFactory = nullptr; //kennt alle angeschlossenen devices
	IDXGIAdapter1* graphicsAdapter = nullptr; //kennt die graphickarten
	DXGI_ADAPTER_DESC adapterDesc = {};//die informationen über die graphikkarte
	IDXGIOutput* adapterOutput = nullptr; //beschreibt meine monitore
	unsigned int displayModeCount = 0; //anzahl der unterstützen bildschirme
	DXGI_MODE_DESC* displayMode = nullptr; //der array in dem die informationen aller unterstützten bildschirme beinhalted

	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&graphicsFactory)))) {
		std::cerr << "failed to create grapphics factor." << std::endl;
		return false;
	}
	if (FAILED(graphicsFactory->EnumAdapters1(0, (&graphicsAdapter)))) {
		std::cerr << "failed to enumerate graphics adapter." << std::endl;
		return false;
	}
	if (FAILED(graphicsAdapter->EnumOutputs(0, &adapterOutput))) {
		std::cerr << "failed to enumerate adapter outputs." << std::endl;
		return false;
	}
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModeCount, NULL))) {
		std::cerr << "failed to retrieve display mode list." << std::endl;
		return false;
	}

	displayMode = new DXGI_MODE_DESC[displayModeCount];
	if (!displayMode) {
		std::cerr << "failed to allocate Display Mode array." << std::endl;
		return false;
	}
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &displayModeCount, displayMode))) {
		std::cerr << "failed to retrieve mode list." << std::endl;
		return false;
	}

	int refreshNumerator = 0;
	int refreshDenominator = 0;
	for (int i = 0; i < displayModeCount; i++) {
		if (displayMode[i].Width != myWindow.GetWidth() || displayMode[i].Height != myWindow.GetHeight())
			continue;

		refreshNumerator = displayMode[i].RefreshRate.Numerator;
		refreshDenominator = displayMode[i].RefreshRate.Denominator;
	}

	if (FAILED(graphicsAdapter->GetDesc(&adapterDesc))) {
		std::cerr << "failed to retrieve adapter descridption." << std::endl;
		return false;
	}

	this->vRAM = adapterDesc.DedicatedVideoMemory * BYTE_TO_MEGABYTE;

	this->vDesc = new char[128];
	//size_t convertedChars = 0;
	wcstombs(this->vDesc, adapterDesc.Description, 128);

	std::cout << "Device selected: " << this->vDesc << " @ " << this->vRAM << std::endl;

	SAFE_DELETE_ARR(displayMode);
	SAFE_RELEASE(adapterOutput);
	SAFE_RELEASE(graphicsAdapter);
	SAFE_RELEASE(graphicsFactory);

	DXGI_SWAP_CHAIN_DESC scDesc = {}; //swap chain descriptor

	scDesc.BufferCount = 2;
	scDesc.BufferDesc.Width = myWindow.GetWidth();
	scDesc.BufferDesc.Height = myWindow.GetHeight();
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	scDesc.BufferDesc.RefreshRate.Numerator = (this->isVSync ? refreshNumerator : 0);
	scDesc.BufferDesc.RefreshRate.Denominator = (this->isVSync && refreshDenominator > 0 ? refreshDenominator : 1);

	std::cout << "Resolution selected: " << myWindow.GetWidth() << " x " << myWindow.GetHeight() << " @ " << scDesc.BufferDesc.RefreshRate.Numerator / scDesc.BufferDesc.RefreshRate.Denominator << std::endl;

	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scDesc.OutputWindow = myWindow.GetHandle();

	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;

	scDesc.Windowed = !enableFullscreen;

	scDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	scDesc.Flags = 0;

	unsigned int debugFlag = 0;

#ifdef _DEBUG
	debugFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		debugFlag,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&scDesc,
		&this->swapChan,
		&this->device,
		NULL,
		&this->context))) {
		std::cerr << "Failed to create a device and a swap chain." << std::endl;
		return false;
	}

	ID3D11Texture2D* backBuffer;
	if (FAILED(this->swapChan->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)(&backBuffer)))) {
		std::cerr << "Failed to retrieve the back buffer." << std::endl;
		return false;
	}
	if (FAILED(this->device->CreateRenderTargetView(backBuffer, NULL, &this->renderTargetView))) {
		std::cerr << "Failed to create a render target view." << std::endl;
		return false;
	}

	SAFE_RELEASE(backBuffer);

	D3D11_TEXTURE2D_DESC dbDesc = {};

	dbDesc.Width = myWindow.GetWidth();
	dbDesc.Height = myWindow.GetHeight();
	dbDesc.MipLevels = 1;
	dbDesc.ArraySize = 1;
	dbDesc.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	dbDesc.SampleDesc.Count = 1;
	dbDesc.SampleDesc.Quality = 0;
	dbDesc.Usage = D3D11_USAGE_DEFAULT;
	dbDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dbDesc.CPUAccessFlags = 0;
	dbDesc.MiscFlags = 0;

	if (FAILED(this->device->CreateTexture2D(&dbDesc, NULL, &this->depthStencilBuffer))) {
		std::cerr << "Failed to create depth stencil buffer." << std::endl;
		return false;
	}

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(this->device->CreateDepthStencilState(&dsDesc, &this->depthStencilState))) {
		std::cerr << "Failed to create depth stencil state." << std::endl;
		return false;
	}

	this->context->OMSetDepthStencilState(this->depthStencilState, 1);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

	dsvDesc.Format = dbDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	if (FAILED(this->device->CreateDepthStencilView(this->depthStencilBuffer, &dsvDesc, &this->depthStencilView))) {
		std::cerr << "Failed to create a depth stencil view." << std::endl;
		return false;
	}

	this->context->OMSetRenderTargets(1, &this->renderTargetView, this->depthStencilView);

	D3D11_RASTERIZER_DESC rDesc = {};

	rDesc.AntialiasedLineEnable = false;
	rDesc.CullMode = D3D11_CULL_BACK;
	rDesc.DepthBias = 0;
	rDesc.DepthBiasClamp = 0.0f;
	rDesc.DepthClipEnable = true;
	rDesc.FillMode = D3D11_FILL_SOLID;
	rDesc.FrontCounterClockwise = true;
	rDesc.MultisampleEnable = false;
	rDesc.ScissorEnable = false;
	rDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(this->device->CreateRasterizerState(&rDesc, &this->rasterState))) {
		std::cerr << "Failed to create a Rasterizer state." << std::endl;
		return false;
	}

	this->context->RSSetState(this->rasterState);

	D3D11_VIEWPORT viewPort = {};

	viewPort.Width = (float)myWindow.GetWidth();
	viewPort.Height = (float)myWindow.GetHeight();
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;

	this->context->RSSetViewports(1, &viewPort);

	if (!this->CreateBuffer() || !this->CreateShader()) {
		return false;
	}

	return true;
}

void Renderer::BeginRender() const {
	float Color[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->context->ClearRenderTargetView(this->renderTargetView, Color);
	this->context->ClearDepthStencilView(this->depthStencilView, D3D11_CLEAR_DEPTH /*| D3D11_CLEAR_STENCIL*/, 0.0f, 0);

	D3D11_MAPPED_SUBRESOURCE mappedCameraResource = {};

	Vector3 camPos = Vector3(0.0f, 0.0f, 2.0f);

	Matrix4x4 vp =
		Matrix4x4::FromPerspetiveFOV(90.0f, 1.77778f /*TODO: get aspect from Window*/, 1000.0f, 0.001f)
		* Matrix4x4::FromView(camPos);

	this->context->Map(this->cameraConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedCameraResource);

	auto cameraData = reinterpret_cast<CameraConstType*>(mappedCameraResource.pData);

	cameraData->modelViewProjection = vp;
	cameraData->camPos = camPos;

	this->context->Unmap(this->cameraConstBuffer, 0);
}

void Renderer::RenderQuad(const Transform& transform) const {
	unsigned int stribe = sizeof(VertexType);
	unsigned int offset = 0;

	D3D11_MAPPED_SUBRESOURCE mappedModelResource = {};

	this->context->Map(this->modelConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedModelResource);

	auto modelData = reinterpret_cast<ModelConstType*>(mappedModelResource.pData);

	modelData->model = transform.GetTransformMatrix();

	this->context->Unmap(this->modelConstBuffer, 0);

	this->context->IASetVertexBuffers(0, 1, &this->vertexBuffer, &stribe, &offset);
	this->context->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	this->context->IASetInputLayout(this->inputLayout);

	this->context->VSSetConstantBuffers(0, 1, &this->cameraConstBuffer);
	this->context->VSSetConstantBuffers(1, 1, &this->modelConstBuffer);

	this->context->VSSetShader(this->vertexShader, NULL, 0);
	this->context->PSSetShader(this->pixelShader, NULL, 0);

	this->context->OMSetRenderTargets(1, &this->renderTargetView, this->depthStencilView);
	this->context->DrawIndexed(this->indexBufferCount, 0, 0);

	this->context->VSSetShader(nullptr, NULL, 0);
	this->context->PSSetShader(nullptr, NULL, 0);
}

/*
void Renderer::RenderMesh(Mesh& mesh, Material* mat) const {
	assert(false && "not implimented");

	unsigned int stribe = sizeof(VertexType);
	unsigned int offset = 0;

	this->context->IASetVertexBuffers(0, 1, &mesh.vertexBuffer, &stribe, &offset);
	this->context->IASetIndexBuffer(mesh.indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	this->context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	this->context->IASetInputLayout(this->inputLayout);

	this->context->VSSetConstantBuffers(0, 1, &this->constBuffer);

	this->context->VSSetShader(this->vertexShader, NULL, 0);
	this->context->PSSetShader(this->pixelShader, NULL, 0);

	this->context->DrawIndexed(this->indexBufferCount, 0, 0);

	this->context->VSSetShader(nullptr, NULL, 0);
	this->context->PSSetShader(nullptr, NULL, 0);
}
*/

void Renderer::EndRender() const {
	this->swapChan->Present(this->isVSync ? 1 : 0, 0);
}

void Renderer::ShutDown() {
	if (this->swapChan)
		this->swapChan->SetFullscreenState(false, nullptr);

	SAFE_RELEASE(this->modelConstBuffer);
	SAFE_RELEASE(this->cameraConstBuffer);
	SAFE_RELEASE(this->indexBuffer);
	SAFE_RELEASE(this->vertexBuffer);
	SAFE_RELEASE(this->inputLayout);
	SAFE_RELEASE(this->pixelShader);
	SAFE_RELEASE(this->vertexShader);
	SAFE_RELEASE(this->rasterState);
	SAFE_RELEASE(this->depthStencilView);
	SAFE_RELEASE(this->depthStencilState);
	SAFE_RELEASE(this->depthStencilBuffer);
	SAFE_RELEASE(this->renderTargetView);
	SAFE_RELEASE(this->swapChan);
	SAFE_RELEASE(this->context);
	SAFE_RELEASE(this->device);
}

bool Renderer::CreateBuffer() {
	VertexType Vertices[8] = {
		Vector3{-0.5f, 0.5f, -0.5f},	Color{0.88f, 0.1f, 0.11f, 1.0f},	Vector3{-0.57735f, 0.57735f, -0.57735f },	{0.0f, 0.0f},
		Vector3{0.5f, 0.5f, -0.5f},		Color{0.9879f, 0.2f, 0.3f, 1.0f},	Vector3{0.57735f, 0.57735f, -0.57735f },	{0.0f, 0.0f},
		Vector3{-0.5f, -0.5f, -0.5f},	Color{0.876f, 0.12f, 0.25f, 1.0f},	Vector3{-0.57735f, -0.57735f, -0.57735f },	{0.0f, 0.0f},
		Vector3{0.5f, -0.5f, -0.5f},	Color{0.879f, 0.14f, 0.21f, 1.0f},	Vector3{0.57735f, -0.57735f, -0.57735f },	{0.0f, 0.0f},

		Vector3{-0.5f, 0.5f, 0.5f},		Color{0.896f, 0.14f, 0.3f, 1.0f},	Vector3{-0.57735f, 0.57735f, 0.57735f },	{0.0f, 0.0f},
		Vector3{0.5f, 0.5f, 0.5f},		Color{0.997f, 0.23f, 0.2f, 1.0f},	Vector3{0.57735f, 0.57735f, 0.57735f },		{0.0f, 0.0f},
		Vector3{-0.5f, -0.5f, 0.5f},	Color{0.864f, 0.28f, 0.21f, 1.0f},	Vector3{-0.57735f, -0.57735f, 0.57735f },	{0.0f, 0.0f},
		Vector3{0.5f, -0.5f, 0.5f},		Color{0.8124f, 0.25f, 0.25f, 1.0f},	Vector3{0.57735f, -0.57735f, 0.57735f },	{0.0f, 0.0f},
	};

	this->indexBufferCount = 14;
	int Indices[14] =
	{
		0, 2, 1, 3,
		7, 2,
		6, 0,
		4, 1,
		5, 7,
		4, 6
	};

	D3D11_BUFFER_DESC VertexBufferDesc = { };
	D3D11_BUFFER_DESC IndexBufferDesc = { };
	D3D11_BUFFER_DESC CameraConstDesc = { };
	D3D11_BUFFER_DESC ModelBufferDesc = { };
	D3D11_SUBRESOURCE_DATA VertexData = { };
	D3D11_SUBRESOURCE_DATA IndexData = { };

	// Set up static vertex buffer info
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDesc.ByteWidth = sizeof(Vertices);
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.MiscFlags = 0;
	VertexBufferDesc.StructureByteStride = 0;

	VertexData.pSysMem = Vertices;
	VertexData.SysMemPitch = 0;
	VertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer
	if (FAILED(this->device->CreateBuffer(&VertexBufferDesc, &VertexData, &this->vertexBuffer))) {
		printf("Failed to create cube vertex buffer.\n");
		return false;
	}

	// Set up the description of the static index buffer.
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	IndexBufferDesc.ByteWidth = sizeof(Indices);
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.MiscFlags = 0;
	IndexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the index data.
	IndexData.pSysMem = Indices;
	IndexData.SysMemPitch = 0;
	IndexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	if (FAILED(this->device->CreateBuffer(&IndexBufferDesc, &IndexData, &this->indexBuffer))) {
		printf("Failed to create cube index buffer.\n");
		return false;
	}

	// set up camera desc

	CameraConstDesc.Usage = D3D11_USAGE_DYNAMIC;
	CameraConstDesc.ByteWidth = sizeof(CameraConstType);
	CameraConstDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	CameraConstDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	CameraConstDesc.MiscFlags = 0;
	CameraConstDesc.StructureByteStride = 0;

	if (FAILED(this->device->CreateBuffer(&CameraConstDesc, NULL, &this->cameraConstBuffer))) {
		printf("Failed to create matrix buffer.\n");
		return false;
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	ModelBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ModelBufferDesc.ByteWidth = sizeof(ModelConstType);
	ModelBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ModelBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ModelBufferDesc.MiscFlags = 0;
	ModelBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	if (FAILED(this->device->CreateBuffer(&ModelBufferDesc, NULL, &this->modelConstBuffer))) {
		printf("Failed to create matrix buffer.\n");
		return false;
	}

	//this->context->UpdateSubresource(this->constBuffer, 0, NULL, &Matrix4x4::Identity, 0, 0);

	return true;
}

bool Renderer::CreateShader() {
	ID3DBlob* VertexShaderBuffer;
	ID3DBlob* PixelShaderBuffer;

	if (FAILED(D3DReadFileToBlob(L"./data/vs_standard.shader", &VertexShaderBuffer))) {
		std::cerr << "Could not read vertex shader file." << std::endl;
		return false;
	}
	if (FAILED(D3DReadFileToBlob(L"./data/ps_standard.shader", &PixelShaderBuffer))) {
		std::cerr << "Could not read pixel shader file." << std::endl;
		return false;
	}


	if (FAILED(this->device->CreateVertexShader(VertexShaderBuffer->GetBufferPointer()
		, VertexShaderBuffer->GetBufferSize()
		, NULL
		, &this->vertexShader))) {
		std::cerr << "Failed to create vertex shader." << std::endl;
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC VertexLayout[4] = { /*your mom gay*/ };
	VertexLayout[0].SemanticName = "POSITION";
	VertexLayout[0].SemanticIndex = 0;
	VertexLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	VertexLayout[0].InputSlot = 0;
	VertexLayout[0].AlignedByteOffset = 0;
	VertexLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	VertexLayout[0].InstanceDataStepRate = 0;

	VertexLayout[1].SemanticName = "COLOR";
	VertexLayout[1].SemanticIndex = 0;
	VertexLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	VertexLayout[1].InputSlot = 0;
	VertexLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	VertexLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	VertexLayout[1].InstanceDataStepRate = 0;

	VertexLayout[2].SemanticName = "NORMAL";
	VertexLayout[2].SemanticIndex = 0;
	VertexLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	VertexLayout[2].InputSlot = 0;
	VertexLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	VertexLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	VertexLayout[2].InstanceDataStepRate = 0;

	VertexLayout[3].SemanticName = "TEXCOORD";
	VertexLayout[3].SemanticIndex = 0;
	VertexLayout[3].Format = DXGI_FORMAT_R32G32_FLOAT;
	VertexLayout[3].InputSlot = 0;
	VertexLayout[3].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	VertexLayout[3].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	VertexLayout[3].InstanceDataStepRate = 0;

	if (FAILED(this->device->CreateInputLayout(VertexLayout
		, sizeof(VertexLayout)/sizeof(D3D11_INPUT_ELEMENT_DESC)
		, VertexShaderBuffer->GetBufferPointer()
		, VertexShaderBuffer->GetBufferSize()
		, &this->inputLayout))) {
		std::cerr << "Failed to create an input layout." << std::endl;
		return false;
	}

	// Create the vertex shader from the buffer.
	if (FAILED(this->device->CreatePixelShader(PixelShaderBuffer->GetBufferPointer()
		, PixelShaderBuffer->GetBufferSize()
		, NULL
		, &this->pixelShader))) {
		std::cerr << "Failed to create pixel shader." << std::endl;
		return false;
	}

	return true;
}
