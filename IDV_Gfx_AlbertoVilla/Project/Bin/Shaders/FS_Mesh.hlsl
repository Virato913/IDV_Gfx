cbuffer ConstantBuffer {
	float4x4 WVP;
	float4x4 World;
	float4x4 WorldView;
	float4 LightPositions;
}

SamplerState SS;
Texture2D tex0 : register(t0);
Texture2D tex1 : register(t1);

struct VS_OUTPUT {
	float4 hposition : SV_POSITION;
	float4 hnormal   : NORMAL;
	float4 htangent  : TANGENT;
	float4 hbinormal : BINORMAL;
	float2 texture0  : TEXCOORD;
	float4 wposition : TEXCOORD1;
};


float4 FS(VS_OUTPUT input) : SV_TARGET{

	float4 Tan = normalize(input.htangent);
	float4 Bin = normalize(input.hbinormal);
	float4 Norm = normalize(input.hnormal);
	float4 texcolor = tex0.Sample(SS,input.texture0);
	float4 texnormal = tex1.Sample(SS,input.texture0);
	texnormal = texnormal*2.0 - 1.0;
	texnormal = normalize(texnormal);
	texnormal.g = -texnormal.g;

	float4 lightvec = normalize(LightPositions - input.wposition);
	float3x3 TBN = float3x3(Tan.xyz,Bin.xyz,Norm.xyz);
	float4 Normal = float4(normalize(mul(texnormal.xyz,TBN)),1.0);
	float att = clamp(dot(lightvec, Norm), 0.0, 1.0);
	float4 color = att*texcolor;
	return color;
}


