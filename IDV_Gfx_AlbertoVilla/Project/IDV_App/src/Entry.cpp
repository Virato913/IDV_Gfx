#include <IDVDefs.h>

#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>
#include <IDVMath.h>

#define xPI 3.141592653589f
#define ToRadian(d) ((d)*(xPI/180.0f))

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {

	/*XMATRIX44 Position, RotationX, RotationY, RotationZ, Scale, Projection, Final;
	XMatTranslation(Position, 15.0f, -5.0f, 0.0f);
	XMatRotationXLH(RotationX, ToRadian(90.0f));
	XMatRotationYLH(RotationY, ToRadian(15.0f));
	XMatRotationZLH(RotationZ, ToRadian(120.0f));
	XMatScaling(Scale, 1.1f, 1.1f, 1.1f);
	XMatPerspectiveLH(Projection, ToRadian(60.0f), 1280.0f / 720.0f, 1.f, 10000.0f);
	Final = Projection*Scale*RotationX*RotationY*RotationZ*Position;

	printf("Translation\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", Position.m11, Position.m12, Position.m13, Position.m14, Position.m21, Position.m22, Position.m23, Position.m24, Position.m31, Position.m32, Position.m33, Position.m34, Position.m41, Position.m42, Position.m43, Position.m44);
	printf("RotationX\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", RotationX.m11, RotationX.m12, RotationX.m13, RotationX.m14, RotationX.m21, RotationX.m22, RotationX.m23, RotationX.m24, RotationX.m31, RotationX.m32, RotationX.m33, RotationX.m34, RotationX.m41, RotationX.m42, RotationX.m43, RotationX.m44);
	printf("RotationY\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", RotationY.m11, RotationY.m12, RotationY.m13, RotationY.m14, RotationY.m21, RotationY.m22, RotationY.m23, RotationY.m24, RotationY.m31, RotationY.m32, RotationY.m33, RotationY.m34, RotationY.m41, RotationY.m42, RotationY.m43, RotationY.m44);
	printf("RotationZ\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", RotationZ.m11, RotationZ.m12, RotationZ.m13, RotationZ.m14, RotationZ.m21, RotationZ.m22, RotationZ.m23, RotationZ.m24, RotationZ.m31, RotationZ.m32, RotationZ.m33, RotationZ.m34, RotationZ.m41, RotationZ.m42, RotationZ.m43, RotationZ.m44);
	printf("Scale\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", Scale.m11, Scale.m12, Scale.m13, Scale.m14, Scale.m21, Scale.m22, Scale.m23, Scale.m24, Scale.m31, Scale.m32, Scale.m33, Scale.m34, Scale.m41, Scale.m42, Scale.m43, Scale.m44);
	printf("Projection\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", Projection.m11, Projection.m12, Projection.m13, Projection.m14, Projection.m21, Projection.m22, Projection.m23, Projection.m24, Projection.m31, Projection.m32, Projection.m33, Projection.m34, Projection.m41, Projection.m42, Projection.m43, Projection.m44);
	printf("Final\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", Final.m11, Final.m12, Final.m13, Final.m14, Final.m21, Final.m22, Final.m23, Final.m24, Final.m31, Final.m32, Final.m33, Final.m34, Final.m41, Final.m42, Final.m43, Final.m44);*/

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