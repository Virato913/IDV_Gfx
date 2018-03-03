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

bool Parser::Load(/*std::string fName, */std::vector<Coordinates*>& coords, std::vector<Indices*>& indices, std::vector<Normals*>& normals, std::vector<TextureCoordinates*>& uv) {
	std::fstream fFile;
	/*std::vector<Coordinates*> MeshList;
	std::vector<Coordinates*>::iterator it;*/
	std::string sIn;

	fFile.open(/*fName + */"Pig.X", std::ios::in, std::ios::binary);

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
				Coordinates* pivot = new Coordinates;
				fFile >> pivot->x;
				fFile >> cChar;
				fFile >> pivot->y;
				fFile >> cChar;
				fFile >> pivot->z;
				fFile >> cChar;
				fFile >> cChar;
				coords.push_back(pivot);
			}
			fFile >> iIndexCount;
			fFile >> cChar;
			for (int i = 0; i < iIndexCount; i++)
			{
				Indices* pivot = new Indices;
				fFile >> pivot->w;
				fFile >> cChar;
				fFile >> pivot->x;
				fFile >> cChar;
				fFile >> pivot->y;
				fFile >> cChar;
				fFile >> pivot->z;
				fFile >> cChar;
				fFile >> cChar;
				indices.push_back(pivot);
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
				Normals* pivot = new Normals;
				fFile >> pivot->x;
				fFile >> cChar;
				fFile >> pivot->y;
				fFile >> cChar;
				fFile >> pivot->z;
				fFile >> cChar;
				fFile >> cChar;
				normals.push_back(pivot);
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
				TextureCoordinates* pivot = new TextureCoordinates;
				fFile >> pivot->u;
				fFile >> cChar;
				fFile >> pivot->v;
				fFile >> cChar;
				fFile >> cChar;
				uv.push_back(pivot);
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