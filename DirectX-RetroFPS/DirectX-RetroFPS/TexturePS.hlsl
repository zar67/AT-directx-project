struct PS_INPUT
{
    float4 Position : POSITION;
    float2 TextureCoord : TEXCOORD;
	float3 Colour : COLOUR;
};

Texture2D shaderTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 pixelColour = shaderTexture.Sample(samplerState, input.TextureCoord);
    pixelColour *= input.Colour;
	return float4(pixelColour, 1.0f);
}