#include <stdio.h>
#include <IDVParser.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

Parser::Parser()
{
	ftest = 0;
	size = 0;

	meshCount = 0;
}

bool Parser::Load(std::string fileName)
{
	std::vector<vertex>::iterator itVert;
	std::vector<uv>::iterator itUV;
	std::vector<normals>::iterator itNormals;
	std::vector<decldata>::iterator itTangentials;
	std::vector<decldata>::iterator itBinormals;

	std::ifstream fileStream;
	fileStream.open(fileName);

	if (!fileStream.is_open())
	{
		std::cout << "couldnt find " << fileName << "in specified directory" << std::endl;
		return false;
	}
	fileStream.seekg(0, fileStream.beg);
	while (!fileStream.eof())
	{
		fileStream >> a;
		if (a == "Mesh")
		{
			fileStream >> a;
			b = a.substr(0, 5);
			if (b == "mesh_")
			{
				meshCount++;
			}

		}
	}
	fileStream.seekg(0, fileStream.beg);

	for (int i = 0; i < meshCount; i++)
	{
		std::vector<uv> uvbuffer;
		std::vector<vertex> vertexbuffer;
		mesh actual;
		while (true)
		{
			fileStream >> a;
			if (a == "Mesh")
			{
				fileStream >> a;
				b = a.substr(0, 5);
				if (b == "mesh_")
				{
					break;
				}

			}
		}
		fileStream >> c >> actual.vertexCount >> c;
		for (unsigned int i = 0; i < actual.vertexCount; i++)
		{
			vertex vp;
			fileStream >> vp.x >> c >> vp.y >> c >> vp.z >> c >> c;
			vertexbuffer.push_back(vp);
		}
		fileStream >> actual.indexCount >> c;
		for (int i = 0; i < actual.indexCount; i++)
		{
			unsigned short v0, v1, v2;
			fileStream >> c >> c >> v0;
			fileStream >> c >> v1;
			fileStream >> c >> v2;
			fileStream >> c >> c;

			actual.MeshIndex.push_back(v0);
			actual.MeshIndex.push_back(v1);
			actual.MeshIndex.push_back(v2);
		}

		while (true)
		{
			fileStream >> a;
			if (a == "MeshNormals")
			{
				fileStream >> a;
				if (a == "normals")
				{
					break;
				}

			}
		}
		fileStream >> c >> actual.normalsCount >> c;
		for (unsigned int i = 0; i < actual.normalsCount; i++)
		{
			normals np;
			fileStream >> np.nx >> c >> np.ny >> c >> np.nz >> c >> c;
			actual.MeshNorm.push_back(np);
		}

		while (true)
		{
			fileStream >> a;
			if (a == "MeshTextureCoords")
			{
				fileStream >> a;
				if (a == "tc0")
				{
					break;
				}

			}
		}
		fileStream >> c >> actual.uvCount >> c;
		for (unsigned int i = 0; i < actual.uvCount; i++)
		{
			uv uvp;
			fileStream >> uvp.u >> c >> uvp.v >> c >> c;
			uvbuffer.push_back(uvp);
		}
		while (true)
		{
			fileStream >> a;
			if (a == "DeclData")
			{
				break;
			}
		}
		fileStream >> c >> actual.totalObjects >> c;
		for (int i = 0; i < actual.totalObjects; i++)
		{
			unsigned short type;
			fileStream >> c >> c >> c >> c >> type >> c >> c >> c >> c;
			actual.objectTypes.push_back(type);
		}
		fileStream >> actual.decldataCount >> c;
		actual.MeshMeta.resize(actual.decldataCount);
		for (unsigned int i = 0; i < actual.vertexCount; i++)
		{
			for (int j = 0; j < actual.totalObjects; j++)
			{
				decldata meta;
				unsigned int m1, m2, m3;
				fileStream >> m1 >> c >> m2 >> c >> m3 >> c;
				float mx = reinterpret_cast<float&>(m1);
				float my = reinterpret_cast<float&>(m2);
				float mz = reinterpret_cast<float&>(m3);
				meta.mx = mx; meta.my = my; meta.mz = mz;
				actual.MeshMeta[j].decldataset.push_back(meta);
			}
		}
		while (true)
		{
			fileStream >> a;
			if (a == "MeshMaterialList")
			{
				fileStream >> a;
				if (a == "mtls")
				{
					break;
				}
			}
		}
		fileStream >> c >> actual.matInMesh >> c >> actual.totalMaterial >> c;
		actual.MeshMat.resize(actual.matInMesh);
		int getMatId = -1;
		for (int i = 0; i < actual.indexCount; i++)
		{

			fileStream >> getMatId >> c;
			actual.MeshMat[getMatId].materialset.push_back(actual.MeshIndex[(i * 3) + 0]);
			actual.MeshMat[getMatId].materialset.push_back(actual.MeshIndex[(i * 3) + 1]);
			actual.MeshMat[getMatId].materialset.push_back(actual.MeshIndex[(i * 3) + 2]);

		}

		bool cycle = true;
		for (unsigned int i = 0; i < actual.matInMesh; i++)
		{
			std::string normal;
			std::string texture;
			while (cycle)
			{
				fileStream >> a;
				if (a == "EffectParamString")
				{
					fileStream >> c >> a;
					if (a == "\"normalMap\";")
					{
						char brake = 92;
						fileStream >> std::quoted(a);
						if (a.find_last_of(brake) != std::string::npos)
						{
							int last = a.find_last_of(brake);
							normal = a.substr(last + 1, a.size() - last);
						}
						else
							normal = a;
					}
				}


				if (a == "TextureFilename")
				{
					fileStream >> a;
					if (a == "Diffuse")
					{
						cycle = false;
					}
				}
			}
			cycle = true;
			char brake = 92;
			fileStream >> c >> std::quoted(a);
			if (a.find_last_of(brake) != std::string::npos)
			{
				int last = a.find_last_of(brake);
				texture = a.substr(last + 1, a.size() - last);
			}
			else
				texture = a;
			actual.txtbuffer.push_back(texture);
			actual.nrmFileBuffer.push_back(normal);
		}
		for (itVert = vertexbuffer.begin(),
			itUV = uvbuffer.begin(),
			itTangentials = actual.MeshMeta[1].decldataset.begin(),
			itBinormals = actual.MeshMeta[0].decldataset.begin(),
			itNormals = actual.MeshNorm.begin();
			itVert != vertexbuffer.end() &&
			itUV != uvbuffer.end() &&
			itTangentials != actual.MeshMeta[1].decldataset.end() &&
			itBinormals != actual.MeshMeta[0].decldataset.end() &&
			itNormals != actual.MeshNorm.end();
			itVert++, itUV++, itTangentials++, itBinormals++, itNormals++
			)
		{
			vertex vpc;
			vpc.x = (*itVert).x;
			vpc.y = (*itVert).y;
			vpc.z = (*itVert).z;
			vpc.w = (*itVert).w;
			vpc.nx = (*itNormals).nx;
			vpc.ny = (*itNormals).ny;
			vpc.nz = (*itNormals).nz;
			vpc.nw = (*itNormals).nw;
			vpc.tx = (*itTangentials).mx;
			vpc.ty = (*itTangentials).my;
			vpc.tz = (*itTangentials).mz;
			vpc.bx = (*itBinormals).mx;
			vpc.by = (*itBinormals).my;
			vpc.bz = (*itBinormals).mz;
			vpc.u = (*itUV).u;
			vpc.v = (*itUV).v;
			actual.MeshVec.push_back(vpc);
		}



		meshesTotal.push_back(actual);
	}

	fileStream.close();


	return true;


}

void Parser::Read()
{
	
	
}