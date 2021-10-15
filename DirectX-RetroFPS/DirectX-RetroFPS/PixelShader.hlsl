struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float3 Colour : COLOUR;
};

float4 main(PS_INPUT input) : SV_TARGET
{
	return float4(input.Colour, 1.0f);
}