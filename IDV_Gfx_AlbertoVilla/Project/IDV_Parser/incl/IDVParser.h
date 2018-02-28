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
	size_t iFound;
	char cChar, cInput;
	int iVertexCount;
	bool bMeshFound;
	bool Load(/*std::string fName, */std::vector<Coordinates*>& coords);
	Parser();
};

#endif