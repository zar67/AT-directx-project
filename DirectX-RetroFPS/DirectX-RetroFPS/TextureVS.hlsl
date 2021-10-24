struct VS_INPUT
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoord : TEXCOORD;
	float3 Colour : COLOUR;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float3 WorldPosition : WORLD_POSITION;
    float3 Normal : NORMAL;
    float2 TextureCoord : TEXCOORD;
	float3 Colour : COLOUR;
};

cbuffer TRANSFORM_BUFFER
{
    matrix Transform;
    matrix ViewProjectionTransform;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
    output.Position = mul(float4(input.Position, 1.0f), ViewProjectionTransform);
    output.WorldPosition = mul(float4(input.Position, 1.0f), Transform);
    output.Normal = normalize(mul(float4(input.Normal, 0.0f), Transform));
    output.TextureCoord = input.TextureCoord;
	output.Colour = input.Colour;
	
	return output;
}