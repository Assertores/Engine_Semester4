#include "structs.hlsl"

float4 PS_Main(PS_Input Input) : SV_TARGET
{
    float3 LightColor = float3(0.588, 0.02, 0.016);
    float4 LightPos = float4(0.0, 0.0, -5.0, 1.0);
    float3 LightDir = normalize(Input.Position - LightPos).xyz;

    float3 HalfVec = normalize(LightPos - CamPos).xyz;

    float3 Diffuse = saturate(dot(LightDir, Input.Normal.xyz)) * LightColor * Input.Color;
    float3 Specular = pow(saturate(dot(HalfVec, Input.Normal.xyz)), 1.5);
    float3 Emissive = float3(0.0, 0.0, 0.0);// float3(0.286, 0.831, 0.89);

    float4 OutputColor = float4((Diffuse * Specular) + Emissive, 1.0);

    return OutputColor;
}
