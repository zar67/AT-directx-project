#define MAX_SCENE_LIGHTS 8

struct PS_INPUT
{
    float4 Position : POSITION;
    float3 WorldPosition : WORLD_POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoord : TEXCOORD;
	float3 Colour : COLOUR;
};

struct DiffuseData
{
    float3 Position;
    float Strength;
	float3 Colour;
};

cbuffer LIGHT_BUFFER : register(b0)
{
    float3 AmbientColour;
    float AttenuationConstant;

    float AttenuationLinear;
    float AttenuationQuadratic;
    float NumLights;
    float paddingOne;

    DiffuseData DiffuseLighting[MAX_SCENE_LIGHTS];
}

Texture2D shaderTexture : TEXTURE : register(t0);
SamplerState samplerState : SAMPLER : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float4 sampleColour = shaderTexture.Sample(samplerState, input.TextureCoord);
    sampleColour *= float4(input.Colour, 1.0f);
    
    // Calculate Diffuse Lighting
    float3 diffuseLight = AmbientColour;
    float iMax = min(MAX_SCENE_LIGHTS, NumLights);
    
    for (int i = 0; i < iMax; i++)
    {
        float3 vectorToLight = DiffuseLighting[i].Position - input.WorldPosition;
        float distanceToLight = length(vectorToLight);
        float3 directionToLight = vectorToLight / distanceToLight;
    
        float diffuseAttenuation = 1.0f / (AttenuationConstant + AttenuationLinear * distanceToLight + AttenuationQuadratic * (distanceToLight * directionToLight));
        float3 diffuseLightIntensity = max(0, dot(directionToLight, input.Normal));
    
        diffuseLight += diffuseLightIntensity * diffuseAttenuation * DiffuseLighting[i].Colour * DiffuseLighting[i].Strength;
    }
    
    float4 finalColour = float4(saturate(sampleColour.rgb * diffuseLight), sampleColour.a);
    
    return finalColour;
}