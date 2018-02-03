#include <IDVDefs.h>

#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
#include <IDVMath.h>

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {

	XMATRIX44 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16), B(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2), C;

	printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", A.m11, A.m12, A.m13, A.m14, A.m21, A.m22, A.m23, A.m24, A.m31, A.m32, A.m33, A.m34, A.m41, A.m42, A.m43, A.m44);

	XMatTranspose(C, A);

	printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", C.m11, C.m12, C.m13, C.m14, C.m21, C.m22, C.m23, C.m24, C.m31, C.m32, C.m33, C.m34, C.m41, C.m42, C.m43, C.m44);

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