struct VS_Input
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR;
};

float4 PS_Main(VS_Input Input) : SV_TARGET
{
    return Input.Color;
}
