#include "IDVMath.h"

void XMatViewLookAtLH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = lookAt - camPos;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatViewLookAtRH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = camPos - lookAt;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatPerspectiveLH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane) {
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (FarPlane - NearPlane);
	mpout.m[2][3] = 1.0;
	mpout.m[3][2] = -(NearPlane*FarPlane) / (FarPlane - NearPlane);
	mpout.m[3][3] = 0.0f;

}

void XMatPerspectiveRH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane)
{
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (NearPlane - FarPlane);
	mpout.m[2][3] = -1.0;
	mpout.m[3][2] = (NearPlane*FarPlane) / (NearPlane - FarPlane);
	mpout.m[3][3] = 0.0f;
}

void XMatOrthoLH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zf - zn);
	m.m[3][2] = -zn / (zf - zn);
	m.m[3][3] = 1.0f;
}

void XMatOrthoRH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zn - zf);
	m.m[3][2] = zn / (zn - zf);
	m.m[3][3] = 1.0f;
}

void XMATRIX44::Inverse(XMATRIX44 *o) {
#if DOUBLE_FOR_INVERSE
	XMATRIX44_64 tmp64 = XMATRIX44_64(this);
	double det =
#else
	XMATRIX44 tmp64 = *this;
	float det =
#endif
		tmp64.m11*tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m11*tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m11*tmp64.m24*tmp64.m32*tmp64.m43
		+ tmp64.m12*tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m12*tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m33*tmp64.m41
		+ tmp64.m13*tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m13*tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m13*tmp64.m24*tmp64.m31*tmp64.m42
		+ tmp64.m14*tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m14*tmp64.m23*tmp64.m32*tmp64.m41
		- tmp64.m11*tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m11*tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m11*tmp64.m24*tmp64.m33*tmp64.m42
		- tmp64.m12*tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m12*tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m12*tmp64.m24*tmp64.m31*tmp64.m43
		- tmp64.m13*tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m13*tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m32*tmp64.m41
		- tmp64.m14*tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m14*tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m14*tmp64.m23*tmp64.m31*tmp64.m42;
#if DOUBLE_FOR_INVERSE
	if (det == 0.0) {
#else
	if (det == 0.0f) {
#endif
		printf("\n\nThe Universe stopped, no det for Matrix, all ends here.\n\n");
		exit(666);
	}
#if DOUBLE_FOR_INVERSE
	det = 1.0 / det;
	XMATRIX44_64 out;
#else
	det = 1.0f / det;
	XMATRIX44 out;
#endif

	out.m11 = tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m24*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m24*tmp64.m33*tmp64.m42;
	out.m12 = tmp64.m12*tmp64.m34*tmp64.m43 + tmp64.m13*tmp64.m32*tmp64.m44 + tmp64.m14*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m33*tmp64.m44 - tmp64.m13*tmp64.m34*tmp64.m42 - tmp64.m14*tmp64.m32*tmp64.m43;
	out.m13 = tmp64.m12*tmp64.m23*tmp64.m44 + tmp64.m13*tmp64.m24*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m24*tmp64.m43 - tmp64.m13*tmp64.m22*tmp64.m44 - tmp64.m14*tmp64.m23*tmp64.m42;
	out.m14 = tmp64.m12*tmp64.m24*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m34 + tmp64.m14*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m23*tmp64.m34 - tmp64.m13*tmp64.m24*tmp64.m32 - tmp64.m14*tmp64.m22*tmp64.m33;
	out.m21 = tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m24*tmp64.m33*tmp64.m41 - tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m24*tmp64.m31*tmp64.m43;
	out.m22 = tmp64.m11*tmp64.m33*tmp64.m44 + tmp64.m13*tmp64.m34*tmp64.m41 + tmp64.m14*tmp64.m31*tmp64.m43 - tmp64.m11*tmp64.m34*tmp64.m43 - tmp64.m13*tmp64.m31*tmp64.m44 - tmp64.m14*tmp64.m33*tmp64.m41;
	out.m23 = tmp64.m11*tmp64.m24*tmp64.m43 + tmp64.m13*tmp64.m21*tmp64.m44 + tmp64.m14*tmp64.m23*tmp64.m41 - tmp64.m11*tmp64.m23*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m41 - tmp64.m14*tmp64.m21*tmp64.m43;
	out.m24 = tmp64.m11*tmp64.m23*tmp64.m34 + tmp64.m13*tmp64.m24*tmp64.m31 + tmp64.m14*tmp64.m21*tmp64.m33 - tmp64.m11*tmp64.m24*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m34 - tmp64.m14*tmp64.m23*tmp64.m31;
	out.m31 = tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m24*tmp64.m31*tmp64.m42 - tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m24*tmp64.m32*tmp64.m41;
	out.m32 = tmp64.m11*tmp64.m34*tmp64.m42 + tmp64.m12*tmp64.m31*tmp64.m44 + tmp64.m14*tmp64.m32*tmp64.m41 - tmp64.m11*tmp64.m32*tmp64.m44 - tmp64.m12*tmp64.m34*tmp64.m41 - tmp64.m14*tmp64.m31*tmp64.m42;
	out.m33 = tmp64.m11*tmp64.m22*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m41 + tmp64.m14*tmp64.m21*tmp64.m42 - tmp64.m11*tmp64.m24*tmp64.m42 - tmp64.m12*tmp64.m21*tmp64.m44 - tmp64.m14*tmp64.m22*tmp64.m41;
	out.m34 = tmp64.m11*tmp64.m24*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m34 + tmp64.m14*tmp64.m22*tmp64.m31 - tmp64.m11*tmp64.m22*tmp64.m34 - tmp64.m12*tmp64.m24*tmp64.m31 - tmp64.m14*tmp64.m21*tmp64.m32;
	out.m41 = tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m23*tmp64.m32*tmp64.m41 - tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m23*tmp64.m31*tmp64.m42;
	out.m42 = tmp64.m11*tmp64.m32*tmp64.m43 + tmp64.m12*tmp64.m33*tmp64.m41 + tmp64.m13*tmp64.m31*tmp64.m42 - tmp64.m11*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m31*tmp64.m43 - tmp64.m13*tmp64.m32*tmp64.m41;
	out.m43 = tmp64.m11*tmp64.m23*tmp64.m42 + tmp64.m12*tmp64.m21*tmp64.m43 + tmp64.m13*tmp64.m22*tmp64.m41 - tmp64.m11*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m23*tmp64.m41 - tmp64.m13*tmp64.m21*tmp64.m42;
	out.m44 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;

	for (int i = 0; i < 16; i++) {
#if DOUBLE_FOR_INVERSE
		double val = det*out.mat[i];
		(*o).mat[i] = static_cast<float>(val);
#else
		(*o).mat[i] = det*out.mat[i];
#endif
	}
	}

XVECTOR2& XVECTOR2::operator += (const XVECTOR2& other) {
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	return *this;
}
XVECTOR2& XVECTOR2::operator -= (const XVECTOR2& other) {
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	return *this;
}
XVECTOR2& XVECTOR2::operator *= (float times) {
	this->x = this->x * times;
	this->y = this->y * times;
	return *this;
}
XVECTOR2& XVECTOR2::operator /= (float times) {
	this->x = this->x / times;
	this->y = this->y / times;
	return *this;
}

XVECTOR2 XVECTOR2::operator + () const {
	return *this;
}
XVECTOR2 XVECTOR2::operator - () const {
	return XVECTOR2(-this->x, -this->y);
}

XVECTOR2 XVECTOR2::operator + (const XVECTOR2& other) const {
	return XVECTOR2(this->x + other.x, this->y + other.y);
}
XVECTOR2 XVECTOR2::operator - (const XVECTOR2& other) const {
	return XVECTOR2(this->x - other.x, this->y - other.y);
}
XVECTOR2 XVECTOR2::operator * (float times) const {
	return XVECTOR2(this->x * times, this->y * times);
}
XVECTOR2 XVECTOR2::operator / (float times) const {
	return XVECTOR2(this->x / times, this->y / times);
}

bool XVECTOR2::operator == (const XVECTOR2& other) const {
	return ((this->x == other.x) && (this->y == other.y));
}
bool XVECTOR2::operator != (const XVECTOR2& other) const {
	return !(*this == other);
}

void XVECTOR2::Normalize() {
	*this /= this->Length();
}
float XVECTOR2::Length() {
	return (sqrt(pow(this->x, 2) + pow(this->y, 2)));
}

XVECTOR3& XVECTOR3::operator += (const XVECTOR3& other) {
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	this->z = this->z + other.z;
	return *this;
}
XVECTOR3& XVECTOR3::operator -= (const XVECTOR3& other) {
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	this->z = this->z - other.z;
	return *this;
}
XVECTOR3& XVECTOR3::operator *= (float times){
	this->x = this->x * times;
	this->y = this->y * times;
	this->z = this->z * times;
	return *this;
}
XVECTOR3& XVECTOR3::operator /= (float times){
	this->x = this->x / times;
	this->y = this->y / times;
	this->z = this->z / times;
	return *this;
}

XVECTOR3 XVECTOR3::operator + () const{
	return *this;
}
XVECTOR3 XVECTOR3::operator - () const{
	return XVECTOR3(-this->x, -this->y, -this->z);
}

XVECTOR3 XVECTOR3::operator + (const XVECTOR3& other) const{
	return XVECTOR3(this->x + other.x, this->y + other.y, this->z + other.z);
}
XVECTOR3 XVECTOR3::operator - (const XVECTOR3& other) const{
	return XVECTOR3(this->x - other.x, this->y - other.y, this->z - other.z);
}
XVECTOR3 XVECTOR3::operator * (float times) const{
	return XVECTOR3(this->x * times, this->y * times, this->z * times);
}
XVECTOR3 XVECTOR3::operator / (float times) const{
	return XVECTOR3(this->x / times, this->y / times, this->z / times);
}

XVECTOR3 XVECTOR3::operator * (const XVECTOR3& other){
	return other;
}

//friend XVECTOR3 XVECTOR3::operator * (float, const struct XVECTOR3&){
//
//}

bool XVECTOR3::operator == (const XVECTOR3& other) const{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
}
bool XVECTOR3::operator != (const XVECTOR3& other) const{
	return !(*this == other);
}

void XVECTOR3::Normalize(){
	*this /= this->Length();
}
float XVECTOR3::Length(){
	return (sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

XMATRIX44& XMATRIX44::operator *= (const XMATRIX44& other){
	XMATRIX44 pivot = *this;
	this->m11 = (pivot.m11*other.m11) + (pivot.m12*other.m21) + (pivot.m13*other.m31) + (pivot.m14*other.m41);
	this->m12 = (pivot.m11*other.m12) + (pivot.m12*other.m22) + (pivot.m13*other.m32) + (pivot.m14*other.m42);
	this->m13 = (pivot.m11*other.m13) + (pivot.m12*other.m23) + (pivot.m13*other.m33) + (pivot.m14*other.m43);
	this->m14 = (pivot.m11*other.m14) + (pivot.m12*other.m24) + (pivot.m13*other.m34) + (pivot.m14*other.m44);

	this->m21 = (pivot.m21*other.m11) + (pivot.m22*other.m21) + (pivot.m23*other.m31) + (pivot.m24*other.m41);
	this->m22 = (pivot.m21*other.m12) + (pivot.m22*other.m22) + (pivot.m23*other.m32) + (pivot.m24*other.m42);
	this->m23 = (pivot.m21*other.m13) + (pivot.m22*other.m23) + (pivot.m23*other.m33) + (pivot.m24*other.m43);
	this->m24 = (pivot.m21*other.m14) + (pivot.m22*other.m24) + (pivot.m23*other.m34) + (pivot.m24*other.m44);

	this->m31 = (pivot.m31*other.m11) + (pivot.m32*other.m21) + (pivot.m33*other.m31) + (pivot.m34*other.m41);
	this->m32 = (pivot.m31*other.m12) + (pivot.m32*other.m22) + (pivot.m33*other.m32) + (pivot.m34*other.m42);
	this->m33 = (pivot.m31*other.m13) + (pivot.m32*other.m23) + (pivot.m33*other.m33) + (pivot.m34*other.m43);
	this->m34 = (pivot.m31*other.m14) + (pivot.m32*other.m24) + (pivot.m33*other.m34) + (pivot.m34*other.m44);

	this->m41 = (pivot.m41*other.m11) + (pivot.m42*other.m21) + (pivot.m43*other.m31) + (pivot.m44*other.m41);
	this->m42 = (pivot.m41*other.m12) + (pivot.m42*other.m22) + (pivot.m43*other.m32) + (pivot.m44*other.m42);
	this->m43 = (pivot.m41*other.m13) + (pivot.m42*other.m23) + (pivot.m43*other.m33) + (pivot.m44*other.m43);
	this->m44 = (pivot.m41*other.m14) + (pivot.m42*other.m24) + (pivot.m43*other.m34) + (pivot.m44*other.m44);
	return *this;
}
XMATRIX44& XMATRIX44::operator += (const XMATRIX44& other) {
	this->m11 += other.m11;
	this->m12 += other.m12;
	this->m13 += other.m13;
	this->m14 += other.m14;
			  
	this->m21 += other.m21;
	this->m22 += other.m22;
	this->m23 += other.m23;
	this->m24 += other.m24;
			  
	this->m31 += other.m31;
	this->m32 += other.m32;
	this->m33 += other.m33;
	this->m34 += other.m34;
			  
	this->m41 += other.m41;
	this->m42 += other.m42;
	this->m43 += other.m43;
	this->m44 += other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator -= (const XMATRIX44& other){
	this->m11 -= other.m11;
	this->m12 -= other.m12;
	this->m13 -= other.m13;
	this->m14 -= other.m14;
			  
	this->m21 -= other.m21;
	this->m22 -= other.m22;
	this->m23 -= other.m23;
	this->m24 -= other.m24;
			  
	this->m31 -= other.m31;
	this->m32 -= other.m32;
	this->m33 -= other.m33;
	this->m34 -= other.m34;
			  
	this->m41 -= other.m41;
	this->m42 -= other.m42;
	this->m43 -= other.m43;
	this->m44 -= other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator *= (float times){
	this->m11 *= times;
	this->m12 *= times;
	this->m13 *= times;
	this->m14 *= times;
			  	 
	this->m21 *= times;
	this->m22 *= times;
	this->m23 *= times;
	this->m24 *= times;
			  	 
	this->m31 *= times;
	this->m32 *= times;
	this->m33 *= times;
	this->m34 *= times;
			  	 
	this->m41 *= times;
	this->m42 *= times;
	this->m43 *= times;
	this->m44 *= times;
	return *this;
}
XMATRIX44& XMATRIX44::operator /= (float times){
	this->m11 /= times;
	this->m12 /= times;
	this->m13 /= times;
	this->m14 /= times;

	this->m21 /= times;
	this->m22 /= times;
	this->m23 /= times;
	this->m24 /= times;

	this->m31 /= times;
	this->m32 /= times;
	this->m33 /= times;
	this->m34 /= times;

	this->m41 /= times;
	this->m42 /= times;
	this->m43 /= times;
	this->m44 /= times;
	return *this;
}

XMATRIX44 XMATRIX44::operator + () const{
	return *this;
}
XMATRIX44 XMATRIX44::operator - () const{
	return XMATRIX44(-this->m11, -this->m12, -this->m13, -this->m14,
					 -this->m21, -this->m22, -this->m23, -this->m24,
					 -this->m31, -this->m32, -this->m33, -this->m34,
					 -this->m41, -this->m42, -this->m43, -this->m44);
}

//XMATRIX44::operator float*(){
//
//}
//XMATRIX44::operator const float* () const{
//
//}

XMATRIX44 XMATRIX44::operator * (const XMATRIX44& other) const{
	return XMATRIX44((this->m11*other.m11) + (this->m12*other.m21) + (this->m13*other.m31) + (this->m14*other.m41),
	(this->m11*other.m12) + (this->m12*other.m22) + (this->m13*other.m32) + (this->m14*other.m42),
	(this->m11*other.m13) + (this->m12*other.m23) + (this->m13*other.m33) + (this->m14*other.m43),
	(this->m11*other.m14) + (this->m12*other.m24) + (this->m13*other.m34) + (this->m14*other.m44),
	(this->m21*other.m11) + (this->m22*other.m21) + (this->m23*other.m31) + (this->m24*other.m41),
	(this->m21*other.m12) + (this->m22*other.m22) + (this->m23*other.m32) + (this->m24*other.m42),
	(this->m21*other.m13) + (this->m22*other.m23) + (this->m23*other.m33) + (this->m24*other.m43),
	(this->m21*other.m14) + (this->m22*other.m24) + (this->m23*other.m34) + (this->m24*other.m44),
	(this->m31*other.m11) + (this->m32*other.m21) + (this->m33*other.m31) + (this->m34*other.m41),
	(this->m31*other.m12) + (this->m32*other.m22) + (this->m33*other.m32) + (this->m34*other.m42),
	(this->m31*other.m13) + (this->m32*other.m23) + (this->m33*other.m33) + (this->m34*other.m43),
	(this->m31*other.m14) + (this->m32*other.m24) + (this->m33*other.m34) + (this->m34*other.m44),
	(this->m41*other.m11) + (this->m42*other.m21) + (this->m43*other.m31) + (this->m44*other.m41),
	(this->m41*other.m12) + (this->m42*other.m22) + (this->m43*other.m32) + (this->m44*other.m42),
	(this->m41*other.m13) + (this->m42*other.m23) + (this->m43*other.m33) + (this->m44*other.m43),
	(this->m41*other.m14) + (this->m42*other.m24) + (this->m43*other.m34) + (this->m44*other.m44));
}
XMATRIX44 XMATRIX44::operator + (const XMATRIX44& other) const{
	return XMATRIX44(this->m11 + other.m11, this->m12 + other.m12, this->m13 + other.m13, this->m14 + other.m14,
					 this->m21 + other.m21, this->m22 + other.m22, this->m23 + other.m23, this->m24 + other.m24,
					 this->m31 + other.m31, this->m32 + other.m32, this->m33 + other.m33, this->m34 + other.m34,
					 this->m41 + other.m41, this->m42 + other.m42, this->m43 + other.m43, this->m44 + other.m44);
}
XMATRIX44 XMATRIX44::operator - (const XMATRIX44& other) const{
	return XMATRIX44(this->m11 + other.m11, this->m12 + other.m12, this->m13 + other.m13, this->m14 + other.m14,
					 this->m21 + other.m21, this->m22 + other.m22, this->m23 + other.m23, this->m24 + other.m24,
					 this->m31 + other.m31, this->m32 + other.m32, this->m33 + other.m33, this->m34 + other.m34,
					 this->m41 + other.m41, this->m42 + other.m42, this->m43 + other.m43, this->m44 + other.m44);
}
XMATRIX44 XMATRIX44::operator * (float times) const{
	return XMATRIX44(this->m11 * times, this->m12 * times, this->m13 * times, this->m14 * times,
					 this->m21 * times, this->m22 * times, this->m23 * times, this->m24 * times,
					 this->m31 * times, this->m32 * times, this->m33 * times, this->m34 * times,
					 this->m41 * times, this->m42 * times, this->m43 * times, this->m44 * times);
}
XMATRIX44 XMATRIX44::operator / (float times) const{
	return XMATRIX44(this->m11 / times, this->m12 / times, this->m13 / times, this->m14 / times,
					 this->m21 / times, this->m22 / times, this->m23 / times, this->m24 / times,
					 this->m31 / times, this->m32 / times, this->m33 / times, this->m34 / times,
					 this->m41 / times, this->m42 / times, this->m43 / times, this->m44 / times);
}

//friend XMATRIX44 XMATRIX44::operator * (float, const XMATRIX44&){}

bool XMATRIX44::operator == (const XMATRIX44& other) const {
	return ((this->m11 == other.m11) && (this->m12 == other.m12) && (this->m13 == other.m13) && (this->m14 == other.m14) &&
			(this->m21 == other.m21) && (this->m22 == other.m22) && (this->m23 == other.m23) && (this->m24 == other.m24) &&
			(this->m31 == other.m31) && (this->m32 == other.m32) && (this->m33 == other.m33) && (this->m34 == other.m34) &&
			(this->m41 == other.m41) && (this->m42 == other.m42) && (this->m43 == other.m43) && (this->m44 == other.m44));
}
bool XMATRIX44::operator != (const XMATRIX44& other) const{
	return (!(*this == other));
}