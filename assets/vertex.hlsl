#pragma pack_matrix( row_major )

cbuffer ConstantBuffer : register(b0) {
    float4x4 MVP;
};

struct VSOutput {
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

VSOutput VSMain(float3 position : POSITION, float4 color : COLOR)
{
    VSOutput result;

    result.Position = mul(MVP, float4(position, 1.0));
    result.Color = color;

    return result;
}