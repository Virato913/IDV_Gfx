#include <IDVParser.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

//void PrintFromLibrary() {
//	printf("Hello World from Static Library\n");
//}

Parser::Parser() {
	iFound = 0;
	iVertexCount = 0;
	bMeshFound = false;
}

bool Parser::Load(/*std::string fName, *//*std::vector<Coordinates>& coords, std::vector<Indices>& indices*//*, std::vector<Normals*>& normals, std::vector<TextureCoordinates*>& uv*/) {
	std::fstream fFile;
	/*std::vector<Coordinates*> MeshList;
	std::vector<Coordinates*>::iterator it;*/
	std::string sIn;

	fFile.open(/*fName + */"CerdoNuevo.X", std::ios::in, std::ios::binary);

	if (fFile.is_open())
	{
		while (!bMeshFound)
		{
			getline(fFile, sIn);
			iFound = sIn.find(" Mesh ");
			if (iFound == 0)
			{
				fFile >> iVertexCount;
				fFile >> cChar;
				bMeshFound = true;
			}
		}
		if (bMeshFound)
		{
			for (int i = 0; i < iVertexCount; i++)
			{
				Coordinates pivot;
				fFile >> pivot.x;
				fFile >> cChar;
				fFile >> pivot.y;
				fFile >> cChar;
				fFile >> pivot.z;
				fFile >> cChar;
				fFile >> cChar;
				coords.push_back(pivot);
			}
			fFile >> iIndexCount;
			fFile >> cChar;
			for (int i = 0; i < iIndexCount; i++)
			{
				/*Indices pivot;*/
				unsigned short pivot;
				fFile >> cChar;
				fFile >> cChar;
				fFile >> pivot;
				index.push_back(pivot);
				fFile >> cChar;
				fFile >> pivot;
				index.push_back(pivot);
				fFile >> cChar;
				fFile >> pivot;
				index.push_back(pivot);
				fFile >> cChar;
				fFile >> cChar;
			}
			bMeshFound = false;
		}
		while (!bMeshFound)
		{
			getline(fFile, sIn);
			iFound = sIn.find("  MeshNormals ");
			if (iFound == 0)
			{
				fFile >> iVertexCount;
				fFile >> cChar;
				bMeshFound = true;
			}
		}
		if (bMeshFound)
		{
			for (int i = 0; i < iVertexCount; i++)
			{
				/*Normals* pivot = new Normals;*/
				/*fFile >> pivot->x;
				fFile >> cChar;
				fFile >> pivot->y;
				fFile >> cChar;
				fFile >> pivot->z;
				fFile >> cChar;
				fFile >> cChar;*/
				/*normals.push_back(pivot);*/
				fFile >> coords[i].nx;
				fFile >> cChar;
				fFile >> coords[i].ny;
				fFile >> cChar;
				fFile >> coords[i].nz;
				fFile >> cChar;
				fFile >> cChar;
			}
			bMeshFound = false;
		}
		while (!bMeshFound)
		{
			getline(fFile, sIn);
			iFound = sIn.find("  MeshTextureCoords ");
			if (iFound == 0)
			{
				fFile >> iVertexCount;
				fFile >> cChar;
				bMeshFound = true;
			}
		}
		if (bMeshFound)
		{
			for (int i = 0; i < iVertexCount; i++)
			{
				/*TextureCoordinates* pivot = new TextureCoordinates;
				fFile >> pivot->u;
				fFile >> cChar;
				fFile >> pivot->v;
				fFile >> cChar;
				fFile >> cChar;
				uv.push_back(pivot);*/
				fFile >> coords[i].u;
				fFile >> cChar;
				fFile >> coords[i].v;
				fFile >> cChar;
				fFile >> cChar;
			}
			bMeshFound = false;
		}
		while (!bMeshFound)
		{
			getline(fFile, sIn);
			iFound = sIn.find("  DeclData");
			if (iFound == 0)
			{
				fFile >> iDeclDataCount;
				fFile >> cChar;
				bMeshFound = true;
			}
		}
		if (bMeshFound)
		{
			DeclData pivotTang, pivotBinom;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> pivotTang.id;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> pivotBinom.id;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			fFile >> cChar;
			getline(fFile, sIn);
			getline(fFile, sIn);
			for (int i = 0; i < iVertexCount; i++)
			{
				unsigned int pivot;
				fFile >> pivot;
				pivotTang.x = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				fFile >> pivot;
				pivotTang.y = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				fFile >> pivot;
				pivotTang.z = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				tang.push_back(pivotTang);
				fFile >> pivot;
				pivotBinom.x = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				fFile >> pivot;
				pivotBinom.y = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				fFile >> pivot;
				pivotBinom.z = reinterpret_cast<float&>(pivot);
				fFile >> cChar;
				binomials.push_back(pivotBinom);
			}
			bMeshFound = false;
		}
		while (!bMeshFound)
		{
			getline(fFile, sIn);
			iFound = sIn.find("  MeshMaterialList");
			if (iFound == 0)
			{
				fFile >> iMaterialsCount;
				fFile >> cChar;
				bMeshFound = true;
			}
		}
		if (bMeshFound)
		{
			int iMatCount;
			fFile >> iMatCount;
			fFile >> cChar;
			getline(fFile, sIn);
			for (int j = 0; j < iMaterialsCount; ++j)
			{
				std::vector<unsigned short> matList;
				for (int i = 0; i < iIndexCount; i++)
				{
					unsigned short pivot;
					fFile >> pivot;
					fFile >> cChar;
					matList.push_back(pivot);
					fFile >> pivot;
					fFile >> cChar;
					matList.push_back(pivot);
					fFile >> pivot;
					fFile >> cChar;
					matList.push_back(pivot);
				}
				materials.push_back(matList);
			}
			bMeshFound = false;
		}
		fFile.close();
		return true;
	}
	else
	{
		return false;
	}
}