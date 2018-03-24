#ifndef IDV_PRIMITIVEMANAGER_H
#define IDV_PRIMITIVEMANAGER_H

#include <d3dx9math.h>
#include <IDVMath.h>

#include <vector>

#include <IDVVideo/IDVBaseDriver.h>
#include <IDVScene/IDVPrimitive.h>
#include <IDVScene/IDVSceneProp.h>

class IDVPrimitiveManager {
public:
	IDVPrimitiveManager(IDVAPI Selected) { SelectedApi = Selected;  }
	void SetVP(/*D3DXMATRIX*/XMATRIX44 *vp) {
		pVP = vp;
	}
	int  CreateQuad();
	int CreateMesh();
	void SetSceneProps(IDVSceneProps *p);

	void DrawPrimitives();
	void DestroyPrimitives();
	IDVPrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<IDVPrimitiveBase*> primitives;

	IDVAPI		SelectedApi;
	/*D3DXMATRIX*/XMATRIX44 *pVP;
};

#endif
