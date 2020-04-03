cbuffer MatrixBuffer
{
	matrix MVP;
};

struct VS_Input
{
	float4 Position : POSITION;
	float4 Color    : COLOR;
};

struct PS_Input
{
	float4 Position : SV_POSITION;
	float4 Color    : COLOR;
};

PS_Input VS_Main(VS_Input Input)
{
	PS_Input Output;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	Output.Position = mul(float4(Input.Position.xyz, 1.0), MVP);

	// Store the input color for the pixel shader to use.
	Output.Color = Input.Color;

	return Output;
}
