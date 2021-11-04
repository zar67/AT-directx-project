#define MAX_SCENE_LIGHTS 4

struct PS_INPUT
{
    float4 Position : POSITION;
    float3 WorldPosition : WORLD_POSITION;
    float3 Normal : NORMAL;
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
    float paddingOne;
    float paddingTwo;

    DiffuseData DiffuseLighting[MAX_SCENE_LIGHTS];
}

float4 main(PS_INPUT input) : SV_TARGET
{
    // Calculate Diffuse Lighting
    float3 diffuseLight = AmbientColour;
    for (int i = 0; i < MAX_SCENE_LIGHTS; i++)
    {
        float3 vectorToLight = DiffuseLighting[i].Position - input.WorldPosition;
        float distanceToLight = length(vectorToLight);
        float3 directionToLight = vectorToLight / distanceToLight;
    
        float diffuseAttenuation = 1.0f / (AttenuationConstant + AttenuationLinear * distanceToLight + AttenuationQuadratic * (distanceToLight * directionToLight));
        float3 diffuseLightIntensity = max(0, dot(directionToLight, input.Normal));
    
        diffuseLight += diffuseLightIntensity * diffuseAttenuation * DiffuseLighting[i].Colour * DiffuseLighting[i].Strength;
    }
    
    float3 finalColour = saturate(input.Colour * diffuseLight);
    
    return float4(finalColour, 1.0f);
}