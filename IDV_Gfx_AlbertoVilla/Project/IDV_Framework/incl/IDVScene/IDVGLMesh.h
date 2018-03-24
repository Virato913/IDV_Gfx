#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H

#include <d3dx9math.h>

#include <GL/glew.h>
#include <IDVMath.h>
#include <IDVParser.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>
#include <IDVParser.h>
#include <map>
#include <string>

class GLMesh : public IDVPrimitiveBase {
public:

	struct SubsetInfo {
		unsigned int				Id;
	};
	struct MeshInfo {
		unsigned int		VB;
		unsigned int		IB;
		std::vector <SubsetInfo>    SubSets;
	};

	GLMesh(){
	
	}
	void Create();
	void Create(char *) {}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();
	std::vector<MeshInfo>		Mesh_Info;
	unsigned int	SigBase;
	unsigned int	VB;
	unsigned int	IB;
	XMATRIX44		transform;

	int			 TexId;
	Texture		*pTexture;
	std::map<std::string, Texture*> textureMap;
	Parser parser;
};

#endif
