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
    float AttenuationConstant;
    float3 AmbientColour;
    float AttenuationLinear;
    float AttenuationQuadratic;
}

Texture2D shaderTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float3 sampleColour = shaderTexture.Sample(samplerState, input.TextureCoord);
    sampleColour *= input.Colour;
    
    float3 vectorToLight = LightPosition - input.WorldPosition;
    float distanceToLight = length(vectorToLight);
    float3 directionToLight = vectorToLight / distanceToLight;
    
    float diffuseAttenuation = 1.0f / (AttenuationConstant + AttenuationLinear * distanceToLight + AttenuationQuadratic * (distanceToLight * directionToLight));
    float3 diffuseLightIntensity = max(0, dot(directionToLight, input.Normal));
    
    float3 diffuseLight = diffuseLightIntensity * diffuseAttenuation * LightColour * LightStrength;
    
    float3 finalColour = saturate(sampleColour * (diffuseLight + AmbientColour));
    
    return float4(finalColour, 1.0f);
}