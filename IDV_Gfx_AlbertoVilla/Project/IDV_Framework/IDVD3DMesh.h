#ifndef IDV_MESH_D3D_H
#define IDV_MESH_D3D_H

#include <d3dx9math.h>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <IDVMath.h>
#include <IDVParser.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>

class D3DXMesh : public PrimitiveBase {
public:
	struct Vert {
		float x, y, z, w;
		float u, v;
	};

	struct CBuffer {
		/*D3DXMATRIX*/XMATRIX44 WVP;
		/*D3DXMATRIX*/XMATRIX44 World;
		/*D3DXMATRIX*/XMATRIX44 WorldView;
	};

	D3DXMesh() {

	}

	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	ComPtr<ID3D11Buffer>		IB;
	ComPtr<ID3D11Buffer>		VB;
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	CBuffer			CnstBuffer;
	Vert			vertices[4];
	unsigned short	indices[6];

	/*D3DXMATRIX*/XMATRIX44		transform;

	Parser Mesh;
	std::vector<Parser::Coordinates*> coords;
	std::vector<Parser::Indices*> index;
	std::vector<Parser::Normals*> normals;
	std::vector<Parser::TextureCoordinates*> uv;
};

#endif