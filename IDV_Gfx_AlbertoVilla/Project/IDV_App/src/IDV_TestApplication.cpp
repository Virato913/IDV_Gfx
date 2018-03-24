#include <IDV_TestApplication.h>

#include <stdio.h>
#include <IDVMath.h>
#include <IDVUtils\Timer.h>



void IDVTestApplication::InitVars() {
	MainCamera.Init(XVECTOR3(0.0f, 1.0f, -10.0f), Deg2Rad(100.0f), (16.0f / 9.0f), 0.1f, 10000, 1);
	TimeManager.Init();
}

void IDVTestApplication::CreateAssets() {
	/*D3DXMATRIX*/XMATRIX44 VP;

	PrimitiveMgr = new IDVPrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	//int index = PrimitiveMgr->CreateQuad();
	int index = PrimitiveMgr->CreateMesh();
	
	//for(int i = 0; i <  ; i++ )
	int i = 0;
	Models[i].CreateInstance(PrimitiveMgr->GetPrimitive(index), &MainCamera.VP);
}

void IDVTestApplication::DestroyAssets() {
	delete PrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {

	OnDraw();
	MainCamera.Update(1.0f);
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	Models[0].Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {
	for (int i = 0; i< MAXKEYS; i++)
	{
		if (i == 119 && inputManager.KeyStates[0][i] == true)
		{
			TimeManager.GetDTSecs();
			MainCamera.MoveForward(2.0f);
		}
		else if (i == 97 && inputManager.KeyStates[0][i] == true)
		{
			TimeManager.GetDTSecs();
			MainCamera.StrafeLeft(2.0f);
		}
		else if (i == 115 && inputManager.KeyStates[0][i] == true)
		{
			TimeManager.GetDTSecs();
			MainCamera.MoveBackward(2.0f);
		}
		else if (i == 100 && inputManager.KeyStates[0][i] == true)
		{
			TimeManager.GetDTSecs();
			MainCamera.StrafeRight(2.0f);
		}
	}
}