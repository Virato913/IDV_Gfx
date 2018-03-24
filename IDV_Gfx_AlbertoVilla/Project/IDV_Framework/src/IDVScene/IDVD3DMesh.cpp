#include <IDVVideo/IDVD3DXShader.h>
#include <IDVScene/IDVD3DMesh.h>
#include <IDVUtils/IDVUtils.h>
#include <IDVParser.h>
#include <IDVVideo/IDVD3DTexture.h>
#include <string>

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;




void D3DXMesh::Create()
{


	HRESULT hr;
	SigBase = IDVSig::HAS_TEXCOORDS0 | IDVSig::HAS_NORMALS;
	//| IDVSig::HAS_TANGENTS | IDVSig::HAS_BINORMALS;

	char *vsSourceP = file2string("Shaders/VS_Mesh.hlsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.hlsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	parser.CargarVertices();

	Mesh_Info.reserve(parser.meshCount);

	for (int i = 0; i < parser.meshCount; i++)
	{
		Parser::Mesh mesh = parser.totalMeshes[i];
		MeshInfo tempMesh;
		//std::cout << mesh.nombresTexturas << std::endl;
		int shaderID = g_pBaseDriver->CreateShader(vstr, fstr, SigBase);
		IDVD3DXShader* s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderIdx(shaderID));
		D3D11_BUFFER_DESC bdesc = { 0 };
		bdesc.Usage = D3D11_USAGE_DEFAULT;
		bdesc.ByteWidth = sizeof(CBuffer);
		bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());

		if (hr != S_OK) {
			printf("Error Creating Constant Buffer\n");
			return;
		}

		bdesc = { 0 };
		bdesc.ByteWidth = mesh.totalVertex * sizeof(Parser::Vertex);
		bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subData = { &mesh.TotalVertex[0], 0, 0 };

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tempMesh.VB);

		if (hr != S_OK) {
			printf("Error Creating Vertex Buffer\n");
			return;
		}

		bdesc = { 0 };
		bdesc.ByteWidth = mesh.indexCoordinatesMesh.size() * sizeof(unsigned short);
		bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		subData = { &mesh.indexCoordinatesMesh[0], 0, 0 };

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tempMesh.IB);
		if (hr != S_OK) {
			printf("Error Creating Index Buffer\n");
			return;
		}

		

		for (int j = 0; j < mesh.totalMaterialsInMesh; j++)
		{
			SubsetInfo tmp_subset;
			bdesc = { 0 };
			bdesc.ByteWidth = mesh.totalMeshMaterials[j].mtlBuffer.size() * sizeof(unsigned short);
			bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			subData = { &mesh.totalMeshMaterials[j].mtlBuffer[0], 0, 0 };
			
			pTexture = new D3DXTexture;

			TexId = pTexture->LoadTexture(mesh.nombresTexturas[j].c_str());


			if (TexId == -1) {
				delete pTexture;
			}
			
			hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tmp_subset.IB);
			if (hr != S_OK) {
				printf("Error Creating Index Buffer\n");
				return;
			}
			tempMesh.SubSets.push_back(tmp_subset);
			textureMap.insert(std::make_pair(mesh.nombresTexturas[j], (pTexture)));
		}
		Mesh_Info.push_back(tempMesh);
	}

	D3D11_SAMPLER_DESC sdesc;
	sdesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.MinLOD = 0;
	sdesc.MaxLOD = D3D11_FLOAT32_MAX;
	sdesc.MipLODBias = 0.0f;
	sdesc.MaxAnisotropy = 1;
	sdesc.BorderColor[0] = sdesc.BorderColor[1] = sdesc.BorderColor[2] = sdesc.BorderColor[3] = 0;
	D3D11Device->CreateSamplerState(&sdesc, pSampler.GetAddressOf());

}

void D3DXMesh::Transform(float *t) {
	transform = t;
}

void D3DXMesh::Draw(float *t, float *vp) {

	if (t)
		transform = t;

	for(int i = 0; i<parser.meshCount; i++)
	{
		MeshInfo drawinfo = Mesh_Info[i];
		Parser::Mesh mesh = parser.totalMeshes[i];
		XMATRIX44 VP = static_cast<XMATRIX44>(vp);
		XMATRIX44 World = static_cast<XMATRIX44>(t);
		
		XMATRIX44 Scale;
		XMATRIX44 View;
		XMATRIX44 Projection;


	/*	XMatViewLookAtLH(View, XVECTOR3(0.0f, 1.0f, -90.0f), XVECTOR3(0.0f, 5.0f, 1.0f), XVECTOR3(0.0f, 100.0f, 0.0f));
		XMatPerspectiveLH(Projection, Deg2Rad(100.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
		XMatScaling(Scale, 1.0f, 1.0f, 1.0f);*/
		

		CnstBuffer.WVP = World*VP;
		CnstBuffer.World = transform;
		CnstBuffer.WorldView = transform;

		unsigned int sig = SigBase;
		sig |= gSig;
		UINT offset = 0;
		UINT stride = sizeof(Parser::Vertex);
		IDVD3DXShader *s = 0;
		D3D11DeviceContext->IASetVertexBuffers(0, 1, drawinfo.VB.GetAddressOf(), &stride, &offset);


		for (int j = 0; j < drawinfo.SubSets.size(); j++)
		{		
			SubsetInfo subinfo = drawinfo.SubSets[j];
			s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderSig(sig));

			D3D11DeviceContext->VSSetShader(s->pVS.Get(), 0, 0);
			D3D11DeviceContext->PSSetShader(s->pFS.Get(), 0, 0);
			D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

			D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
			D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
			D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

			
			D3DXTexture *texd3d = dynamic_cast<D3DXTexture*>(this->textureMap.find(mesh.nombresTexturas[j])->second);
			//D3DXTexture *texd3d = dynamic_cast<D3DXTexture*>(this->textureCollection[j]);
			D3D11DeviceContext->PSSetShaderResources(0, 1, texd3d->pSRVTex.GetAddressOf());
			D3D11DeviceContext->PSSetSamplers(0, 1, texd3d->pSampler.GetAddressOf());

			D3D11DeviceContext->IASetIndexBuffer(subinfo.IB.Get(), DXGI_FORMAT_R16_UINT, 0);
						
			
			D3D11DeviceContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(mesh.totalMeshMaterials[j].mtlBuffer.size(), 0, 0);
		}		
	}
}

void D3DXMesh::Destroy() {
}
