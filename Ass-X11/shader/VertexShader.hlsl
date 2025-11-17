cbuffer cb : register(b0)
{
    matrix mat;
};

float4 main( float3 pos : POSITION ) : SV_POSITION
{
    return mul(float4(pos, 1.0f), mat);
    //return float4(pos, 1.0f);
}