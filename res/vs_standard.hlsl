#include "structs.hlsl"

PS_Input VS_Main(VS_Input Input)
{
	PS_Input Output;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	Output.Position = mul(Input.Position, mul(Model, VP));

	// Store the input color for the pixel shader to use.
	Output.Color = Input.Color;

	Output.Normal = mul(Input.Normal, Model);

	Output.UV = Input.UV;

	return Output;
}
