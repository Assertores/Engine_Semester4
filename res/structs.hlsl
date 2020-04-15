cbuffer CameraConst : register(b0) {
	matrix VP;
	float4 CamPos;
};

cbuffer ModelConst : register(b1) {
	matrix Model;
};

struct VS_Input {
	float4 Position : POSITION0;
	float3 Color    : COLOR0;
	float4 Normal	: NORMAL0;
	float2 UV		: TEXCOORD0;
};

struct PS_Input {
	float4 Position : SV_POSITION;
	float3 Color    : COLOR0;
	float4 Normal	: NORMAL0;
	float2 UV		: TEXCOORD0;
};