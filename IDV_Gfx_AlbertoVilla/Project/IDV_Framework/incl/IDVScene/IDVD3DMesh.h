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
#include<vector>
#include<map>
class D3DXMesh : public IDVPrimitiveBase
{
public:

	struct CBuffer {
		XMATRIX44 WVP;
		XMATRIX44 World;
		XMATRIX44 WorldView;
	};

	struct SubsetInfo {

		ComPtr<ID3D11Buffer>		IB;
	};

	struct MeshInfo {
		ComPtr<ID3D11Buffer>		VB;
		ComPtr<ID3D11Buffer>		IB;
		std::vector <SubsetInfo>    SubSets;
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

	std::vector<MeshInfo>		Mesh_Info;

	CBuffer			CnstBuffer;
	XMATRIX44		transform;
	Parser parser;

	int			 TexId;
	Texture		*pTexture;
	std::vector<Texture*> textureCollection;
	std::map<std::string, Texture*> textureMap;
};

#endif