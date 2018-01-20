#include <IDVParser.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>

//void PrintFromLibrary() {
//	printf("Hello World from Static Library\n");
//}

using namespace std;

Parser::Parser() {
	iFound = 0;
	iVertexCount = 0;
	bMeshFound = false;
}

bool Parser::Load(std::string fName) {
	fstream fFile;
	vector<Coordinates*> MeshList;
	vector<Coordinates*>::iterator it;
	string sIn, sFileName;

	fFile.open(sFileName + ".X", ios::in, ios::binary);

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
				MeshList.push_back(pivot);
			}
			fFile.close();
			return true;
		}
	}
	else
	{
		return false;
	}
}