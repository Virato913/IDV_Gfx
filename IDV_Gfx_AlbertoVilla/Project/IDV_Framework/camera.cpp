#include <IDVUtils/camera.h>

Camera::Camera()
{
	Right = XVECTOR3(1, 0, 0);
	Up = XVECTOR3(0, 1, 0);
}

void Camera::Init(XVECTOR3 position, float fov, float ratio, float np, float fp, bool lf)
{
	XMatTranslation(Position, position);
	Fov = fov;
	AspectRatio = ratio;
	NPlane = np;
	FPlane = fp;
	Yaw = 0;
	Pitch = 0;
	Roll = 0;
	MaxRoll = Deg2Rad(45.0f);
	MaxPitch = Deg2Rad(90.0f);
	MaxYaw = Deg2Rad(360.0f);
	Speed = 10;
	Friction = 1;
	LeftHanded = lf;
	CreatePojection();
	Eye = position;
	SetLookAt(XVECTOR3(0, 0, 0));
	Update(1.0f);
}

void Camera::CreatePojection()
{
	XMatPerspectiveLH(Projection, Fov, AspectRatio, NPlane, FPlane);
}

void Camera::SetLookAt(XVECTOR3 v)
{
	Look = v;
	XMatViewLookAtLH(View, Eye, Look, Up);
}

void Camera::MoveForward(float dt)
{
	XVECTOR3 moveDir = Look - Eye;
	moveDir.Normalize();
	Look += moveDir;
	Eye += moveDir;
}

void Camera::MoveBackward(float dt)
{
	XVECTOR3 moveDir = Look - Eye;
	moveDir.Normalize();
	Look -= moveDir;
	Eye -= moveDir;
}

void Camera::StrafeLeft(float dt)
{
	XVECTOR3 moveDir = XVECTOR3(1, 0, 0);
	moveDir.Normalize();
	Look -= moveDir;
	Eye -= moveDir;
}

void Camera::StrafeRight(float dt)
{
	XVECTOR3 moveDir = XVECTOR3(1, 0, 0);
	moveDir.Normalize();
	Look += moveDir;
	Eye += moveDir;
}


void Camera::MoveYaw(float f)
{
	if (f == 0.0f)
	{
		return;
	}
	XMATRIX44 rotation;
	XMatRotationAxisLH(rotation, Up, f);
	XVecTransformLH(Right, Right, rotation);
	XVecTransformLH(Look, Look, rotation);
}

void Camera::MovePitch(float f)
{
	if (f == 0.0f)
	{
		return;
	}
	Pitch -= f;
	if (Pitch > MaxPitch)
	{
		f += Pitch - MaxPitch;
	}
	else if (Pitch < -MaxPitch)
	{
		f += Pitch + MaxPitch;
	}
	XMATRIX44 rotation;
	XMatRotationAxisLH(rotation, Right, f);
	XVecTransformLH(Up, Up, rotation);
	XVecTransformLH(Look, Look, rotation);
}

void Camera::MoveRoll(float f)
{
	if (f == 0.0f)
	{
		return;
	}
	XMATRIX44 rotation;
	XMatRotationAxisLH(rotation, Look, f);
	XVecTransformLH(Right, Right, rotation);
	XVecTransformLH(Up, Up, rotation);
}

void Camera::Update(float dt)
{
	CreatePojection();
	SetLookAt(Look);
	VP = View*Projection;/*
	XMatViewLookAtLH(View, Eye, Look, Up);
	Right.x = View.m11;
	Right.y = View.m21;
	Right.z = View.m31;
	Up.x = View.m12;
	Up.y = View.m22;
	Up.z = View.m32;
	Look.x = View.m13;
	Look.y = View.m23;
	Look.z = View.m33;

	float lookLengthOnXZ = sqrtf(Look.z * Look.z + Look.x * Look.x);
	Pitch = atan2f(Look.y, lookLengthOnXZ);
	Yaw = atan2f(Look.x, Look.z);*/
}

void Camera::Reset()
{

}

void Camera::SetFov(float f)
{
	Fov = f;
}

void Camera::SetRatio(float r)
{
	AspectRatio = r;
}

void Camera::SetPlanes(float n, float f)
{
	NPlane = n;
	FPlane = f;
}