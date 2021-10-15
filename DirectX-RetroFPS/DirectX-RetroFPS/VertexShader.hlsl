struct VS_INPUT
{
	float2 Position : POSITION;
	float3 Colour : COLOUR;
};

struct VS_OUTPUT
{
	float4 Position : SV_POSITION;
	float3 Colour : COLOUR;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.Position = float4(input.Position, 0.0f, 1.0f);
	output.Colour = input.Colour;
	
	return output;
}