struct PS_INPUT
{
    float4 Position : POSITION;
    float3 WorldPosition : WORLD_POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoord : TEXCOORD;
	float3 Colour : COLOUR;
};

cbuffer LIGHT_BUFFER : register(b0)
{
    float3 LightPosition;
    float LightStrength;
    float3 LightColour;
}

Texture2D shaderTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

static const float3 ambient = { 0.15f, 0.15f, 0.15f };

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleColour = shaderTexture.Sample(samplerState, input.TextureCoord);
    sampleColour *= input.Colour;
    
    float3 vectorToLight = normalize(LightPosition - input.WorldPosition);
    float distanceToLight = length(vectorToLight);
    float3 directionToLight = vectorToLight / distanceToLight;
    
    float diffuseAttenuation = distanceToLight * distanceToLight * directionToLight;
    float3 diffuseLightIntensity = max(0, dot(directionToLight, input.Normal));
    
    float3 diffuseLight = diffuseLightIntensity * diffuseAttenuation * LightColour * LightStrength;
    
    float3 finalColour = sampleColour * saturate(diffuseLight + ambient);
    
    return float4(finalColour, 1.0f);
}