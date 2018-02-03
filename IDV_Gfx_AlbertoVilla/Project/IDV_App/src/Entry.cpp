#include <IDVDefs.h>

#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
#include <IDVMath.h>

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {

	/*XMATRIX44 A(1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4);

	printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", A.m11, A.m12, A.m13, A.m14, A.m21, A.m22, A.m23, A.m24, A.m31, A.m32, A.m33, A.m34, A.m41, A.m42, A.m43, A.m44);

	XMatTranslation(A, 1, 2, 3);

	printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", A.m11, A.m12, A.m13, A.m14, A.m21, A.m22, A.m23, A.m24, A.m31, A.m32, A.m33, A.m34, A.m41, A.m42, A.m43, A.m44);*/

	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	g_pWindow->UpdateApplication();

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;

	return 0;
}