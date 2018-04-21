#pragma once
#ifndef IDV_Parser
#define IDV_Paser
#include <string>
#include <vector>
#include <map>
class Parser
{
public:

	Parser();
	void Read();
	bool Load(std::string fileName);
	struct vertex
	{
		vertex() :
			x(0.0f), y(0.0f), z(0.0f), w(1.0f),
			nx(0.0f), ny(1.0f), nz(0.0f), nw(1.0f),
			tx(0.0f), ty(0.0f), tz(0.0f), tw(1.0f),
			bx(0.0f), by(0.0f), bz(0.0f), bw(1.0f),
			u(0.0f), v(0.0f)
		{}
		float x, y, z, w;
		float nx, ny, nz, nw;
		float tx, ty, tz, tw;
		float bx, by, bz, bw;
		float u, v;

	};
	struct uv
	{
		float u, v;
	};
	struct normals
	{
		float nx, ny, nz, nw;
	};
	struct decldata
	{
		float mx, my, mz;
	};
	struct decldatavector
	{

		std::vector<decldata> decldataset;
	};

	struct materials
	{
		std::vector<unsigned short> materialset;
	};
	struct mesh
	{
		mesh() : vertexCount(0), normalsCount(0), indexCount(0), uvCount(0), decldataCount(0)
		{}
		std::vector<std::string> txtbuffer;
		std::vector<std::string> nrmFileBuffer;
		std::vector<unsigned short> objectTypes;
		std::vector<materials> MeshMat;
		std::vector<decldatavector>MeshMeta;
		std::vector<vertex> MeshVec;
		std::vector<normals> MeshNorm;
		std::vector<unsigned short> MeshIndex;
		unsigned int
			vertexCount, normalsCount, uvCount, decldataCount,
			totalMaterial;
		unsigned short indexCount, totalObjects, matInMesh;
	};
	std::vector<mesh> meshesTotal;
	std::string
		indexchecker,
		a, b;
	int size, meshCount;

	float ftest;
	char c, cont;
};
#endif