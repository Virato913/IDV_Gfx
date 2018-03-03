#include <string>
#include <vector>
#ifndef IDV_PARSER
#define IDV_PARSER

//void PrintFromLibrary();

class Parser {
public: 
	struct Coordinates
	{
		float x, y, z, w = 1.0f;
		float nx, ny, nz, nw = 1.0f;
		float u, v;
	};
	/*struct Indices
	{
		unsigned short x, y, z;
	};*/
	/*struct Normals
	{
		float x, y, z;
	};
	struct TextureCoordinates
	{
		float u, v;
	};*/
	size_t iFound;
	char cChar, cInput;
	int iVertexCount, iIndexCount;
	std::vector<Coordinates> coords;
	std::vector<unsigned short> index;
	bool bMeshFound;
	bool Load(/*std::string fName, *//*std::vector<Coordinates>& coords, std::vector<Indices>& indices*//*, std::vector<Normals*>& normals, std::vector<TextureCoordinates*>& uv*/);
	Parser();
};

#endif