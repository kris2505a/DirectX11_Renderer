Texture2D tex : register(t0);
SamplerState samp : register(s0);

cbuffer filling : register(b0)
{
    float4 color;
};

cbuffer cbLight : register(b1)
{
    float3 lightDir;
    float intensity;
    float3 lightColor;
    float padding;
};

struct VSOut
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

float4 main(VSOut input) : SV_TARGET
{
    //float4 texColor = tex.Sample(samp, input.uv);
    float3 N = normalize(input.normal);
    float3 L = normalize(-lightDir);
    
    //float NdotL = saturate(dot(N, L));
    float NdotL = saturate(dot(input.normal, -lightDir));
    
    float3 lighting = lightColor * NdotL * intensity;
    float3 ambient = 0.1f * lightColor;
    
    float3 finalColor = color.rgb * (ambient + lighting);
    
    //return color;
    
    return float4(finalColor, color.a);
}