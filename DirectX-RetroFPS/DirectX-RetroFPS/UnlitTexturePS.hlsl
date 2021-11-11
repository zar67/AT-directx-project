
struct PS_INPUT
{
    float4 Position : POSITION;
    float3 WorldPosition : WORLD_POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoord : TEXCOORD;
    float3 Colour : COLOUR;
};

Texture2D shaderTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 sampleColour = shaderTexture.Sample(samplerState, input.TextureCoord);
    sampleColour *= float4(input.Colour, 1.0f);

    float4 finalColour = float4(saturate(sampleColour.rgb), sampleColour.a);
    
    return finalColour;
}