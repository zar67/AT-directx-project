struct VS_INPUT
{
    float3 Position : POSITION;
    float3 Colour : COLOUR;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float3 Colour : COLOUR;
};

cbuffer CONSTANT_BUFFER
{
    matrix Transform;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Position = mul(float4(input.Position, 1.0f), Transform);
    output.Colour = input.Colour;
	
    return output;
}