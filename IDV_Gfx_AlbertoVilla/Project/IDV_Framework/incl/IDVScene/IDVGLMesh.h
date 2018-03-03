#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H

#include <d3dx9math.h>

#include <GL/glew.h>
#include <IDVMath.h>
#include <IDVParser.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>

class GLMesh : public PrimitiveBase {
public:
	struct Vert {
		float x, y, z, w;
		float u, v;
	};

	GLMesh() {}
	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	Vert			vertices[4];
	unsigned short	indices[6];
	unsigned int	VB;
	unsigned int	IB;
	/*D3DXMATRIX*/XMATRIX44		transform;

	Parser Mesh;
	/*std::vector<Parser::Coordinates*> coords;
	std::vector<Parser::Indices*> index;*/
};

#endif
