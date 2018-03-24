#include <string>
#include <vector>
#include <string>
#ifndef IDV_PARSER
#define IDV_PARSER

//void PrintFromLibrary();

class Parser
{
public:
	struct Vertex
	{
		float x, y, z, w = 1.0f;
		float xn, yn, zn, wn = 1.0f;
		float u, v;
	};

	struct Index
	{
		float x, y, z;
	};

	struct MetaObject
	{
		float mx, my, mz;
	};

	struct MetaSubset
	{
		std::vector<MetaObject> submeta;
	};

	struct MatSubset
	{
		std::vector<unsigned short> mtlBuffer;
	};


	
	//std::vector<Vertex> vertexVec;

	


	

	//std::vector<std::vector<unsigned short>> indexCoordinatesMesh;
	//std::vector<std::vector<Vertex>> TotalMeshes;
	//std::vector<MatSubset> totalMeshMaterials;
	//std::vector<MetaSubset> meshMetaInfo;
	//std::vector<unsigned short> MaterialType;

	unsigned int meshCount = 0;
	//unsigned int totalVertex, totalIndexes, totalNormals,  totalMeta, totalMaterials;
	//unsigned short type, totalMaterialsInMesh;

	struct Mesh
	{
		std::vector<unsigned short> indexCoordinatesMesh;
		std::vector<Vertex> TotalVertex;
		std::vector<MatSubset> totalMeshMaterials;
		std::vector<MetaSubset> meshMetaInfo;
		std::vector<unsigned short> MaterialType;
		std::vector<std::string> nombresTexturas;
		unsigned int totalVertex, totalIndexes, totalNormals, totalMeta, totalMaterials, totaltext = 0;
		unsigned short type, totalMaterialsInMesh;
	};

	std::vector<Mesh> totalMeshes;


	Parser();
	void CargarVertices();
};

#endif