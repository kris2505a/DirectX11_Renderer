cbuffer cb : register(b0)
{
    matrix mat;
};

cbuffer cb2 : register(b1)
{
    matrix model;
};

struct VSIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

struct VSOut
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

VSOut main(VSIn input) {
    VSOut output;
    output.position = mul(float4(input.pos, 1.0f), mat);
    output.uv = input.uv;
    output.normal = mul(float4(input.normal, 0.0f), model);
    return output;
}