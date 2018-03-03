#include <string>
#include <vector>
#ifndef IDV_PARSER
#define IDV_PARSER

//void PrintFromLibrary();

class Parser {
public: 
	struct Coordinates
	{
		float x, y, z;
	};
	struct Indices
	{
		unsigned short w, x, y, z;
	};
	struct Normals
	{
		float x, y, z;
	};
	struct TextureCoordinates
	{
		float u, v;
	};
	size_t iFound;
	char cChar, cInput;
	int iVertexCount, iIndexCount;
	bool bMeshFound;
	bool Load(/*std::string fName, */std::vector<Coordinates*>& coords, std::vector<Indices*>& indices, std::vector<Normals*>& normals, std::vector<TextureCoordinates*>& uv);
	Parser();
};

#endif