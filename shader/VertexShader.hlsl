cbuffer cb : register(b0)
{
    matrix mat;
};

struct VSIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VSOut
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

VSOut main(VSIn input) {
    VSOut output;
    output.position = mul(float4(input.pos, 1.0f), mat);
    output.uv = input.uv;
    return output;
}