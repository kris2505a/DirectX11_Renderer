cbuffer cb : register(b0)
{
    matrix mat;
};

struct VSIn
{
    float3 pos    : POSITION;
    float4 color  : COLOR;
};

struct VSOut
{
    float4 position    : SV_POSITION;
    float4 color       : COLOR;
};


VSOut main(VSIn input)
{
    VSOut output;
    output.position = mul(float4(input.pos, 1.0f), mat);
    output.color = input.color;
    return output;
}