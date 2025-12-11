Texture2D tex : register(t0);
SamplerState samp : register(s0);

cbuffer filling
{
    float4 color;
};

struct VSOut
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
};

float4 main(VSOut input) : SV_TARGET
{
    //float4 texColor = tex.Sample(samp, input.uv);
    return color;
}