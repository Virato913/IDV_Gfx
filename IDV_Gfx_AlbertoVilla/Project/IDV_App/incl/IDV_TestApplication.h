#ifndef IDV_TEST_APPLICATION
#define IDV_TEST_APPLICATION
#include <IDVMath.h>
#include <IDVBase/IDVCoreBase.h>
#include <IDVScene/IDVPrimitiveManager.h>
#include <IDVScene/IDVSceneProp.h>
#include <IDVScene/IDVPrimitiveInstance.h>
#include <IDVUtils/Camera.h>
#include <IDVUtils/Timer.h>
class IDVTestApplication : public IDVBaseApplication {
public:
	IDVTestApplication() : IDVBaseApplication() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();
	void OnUpdate();
	void OnDraw();
	void OnInput();

	IDVPrimitiveManager *IDVPrimitiveMgr;
	IDVPrimitiveInst	 QuadInst;
	IDVPrimitiveInst	Mesh[10];
	Camera mainCamera;
	Camera* activeCamera;
	IDVLight *Light;
	IDVSceneProps sceneProp;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMATRIX44 Camera;
	Timer TimeManager;
	float deltaTime;
	bool firstFrame;
	int instancesInScene;
};

#endif