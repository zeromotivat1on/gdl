#pragma once

#include "gdlmath.h"
#include "vector.h"

// All matrices follow *row-major* convention.
// All matrix operations follow *right-handed* convention.

struct mat4;
struct quat;

inline constexpr f32 gMatrixEpsilon = 1e-06f;
inline constexpr f32 gMatrixInvEpsilon = 1e-14f;

// Right-handed look at view matrix.
mat4 mat4lookat(const vec3& eye, const vec3& at, const vec3& up);

// Right-handed perspective matrix.
mat4 mat4perspective(f32 rfovy, f32 aspect, f32 n, f32 f);

// Right-handed orthographic matrix.
mat4 mat4orthographic(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);

// Row-major matrix 2x2.
struct mat2
{
    vec2            mat[2];

       				mat2();
	explicit 		mat2(const vec2& x, const vec2& y);
	explicit 		mat2(f32 xx, f32 xy, f32 yx, f32 yy);
	explicit 		mat2(const f32 src[2][2]);

	const vec2&		operator[](s32 index) const;
	vec2&			operator[](s32 index);
	mat2			operator-() const;
   	mat2			operator+(const mat2& a) const;
   	mat2			operator-(const mat2& a) const;
   	mat2			operator*(const mat2& a) const;
	vec2			operator*(const vec2& vec) const;
   	mat2			operator*(f32 a) const;
   	mat2&			operator+=(const mat2& a);
   	mat2&			operator-=(const mat2& a);
	mat2&			operator*=(const mat2& a);
   	mat2&			operator*=(f32 a);

   	bool			operator==(const mat2& a) const;
   	bool			operator!=(const mat2& a) const;

	friend vec2		operator*(const vec2& vec, const mat2& mat);
   	friend mat2		operator*(f32 a, const mat2& mat);
	friend vec2&	operator*=(vec2& vec, const mat2& mat);

	bool			Equal(const mat2& a) const;
	bool			Equal(const mat2& a, f32 epsilon) const;

	mat2&			Zero();
	mat2&			Identity();
	bool			Identity(f32 epsilon = gMatrixEpsilon) const;
	bool			Symmetric(f32 epsilon = gMatrixEpsilon) const;
	bool			Diagonal(f32 epsilon = gMatrixEpsilon) const;

	f32				Trace() const;
	f32				Determinant() const;
	mat2			Transpose() const;
	mat2&			TransposeSelf();
	mat2			Inverse() const;
	bool			InverseSelf();

	s32				Dimension() const;

	const f32*		Ptr() const;
	f32*			Ptr();
};

inline mat2 IdentityMat2()
{
	return mat2(vec2(1.0f, 0.0f), vec2(0.0f, 1.0f));
}

inline mat2::mat2()
{
}

inline mat2::mat2(const vec2& x, const vec2& y)
{
	mat[0] = x;
	mat[1] = y;
}

inline mat2::mat2(f32 xx, f32 xy, f32 yx, f32 yy)
{
	mat[0][0] = xx; mat[0][1] = xy;
	mat[1][0] = yx; mat[1][1] = yy;
}

inline mat2::mat2(const f32 src[2][2])
{
	memcpy(mat, src, 2 * 2 * sizeof(f32));
}

inline const vec2& mat2::operator[](s32 index) const
{
	return mat[index];
}

inline vec2& mat2::operator[](s32 index)
{
	return mat[index];
}

inline mat2 mat2::operator-() const
{
	return mat2
	(
		-mat[0][0], -mat[0][1],
		-mat[1][0], -mat[1][1]
	);
}

inline mat2 mat2::operator+(const mat2& a) const
{
	return mat2
	(
		mat[0][0] + a[0][0], mat[0][1] + a[0][1],
		mat[1][0] + a[1][0], mat[1][1] + a[1][1]
	);
}

inline mat2 mat2::operator-(const mat2& a) const
{
	return mat2
	(
		mat[0][0] - a[0][0], mat[0][1] - a[0][1],
		mat[1][0] - a[1][0], mat[1][1] - a[1][1]
	);
}

inline mat2 mat2::operator*(const mat2& a) const
{
	return mat2
	(
		mat[0][0] * a[0][0] + mat[0][1] * a[1][0],
		mat[0][0] * a[0][1] + mat[0][1] * a[1][1],
		mat[1][0] * a[0][0] + mat[1][1] * a[1][0],
		mat[1][0] * a[0][1] + mat[1][1] * a[1][1]
	);
}

inline vec2 mat2::operator*(const vec2& vec) const
{
	return vec2
	(
		mat[0][0] * vec[0] + mat[0][1] * vec[1],
		mat[1][0] * vec[0] + mat[1][1] * vec[1]
	);
}

inline mat2 mat2::operator*(f32 a) const
{
	return mat2
	(
		mat[0][0] * a, mat[0][1] * a,
		mat[1][0] * a, mat[1][1] * a
	);
}

inline mat2& mat2::operator+=(const mat2& a)
{
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1];
	return *this;
}

inline mat2& mat2::operator-=(const mat2& a)
{
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1];
	return *this;
}

inline mat2& mat2::operator*=(const mat2& a) {
	mat[0][0] = mat[0][0] * a[0][0] + mat[0][1] * a[1][0];
	mat[0][1] = mat[0][0] * a[0][1] + mat[0][1] * a[1][1];
	mat[1][0] = mat[1][0] * a[0][0] + mat[1][1] * a[1][0];
	mat[1][1] = mat[1][0] * a[0][1] + mat[1][1] * a[1][1];
	return *this;
}

inline mat2& mat2::operator*=(f32 a)
{
	mat[0][0] *= a; mat[0][1] *= a;
	mat[1][0] *= a; mat[1][1] *= a;
	return *this;
}

inline bool mat2::operator==(const mat2& a) const
{
	return Equal(a);
}

inline bool mat2::operator!=(const mat2& a) const
{
	return !(*this == a);
}

inline vec2 operator*(const vec2& vec, const mat2& mat)
{
	return mat * vec;
}

inline mat2 operator*(f32 a, const mat2& mat)
{
	return mat * a;
}

inline vec2& operator*=(vec2& vec, const mat2& mat)
{
	vec = mat * vec;
	return vec;
}

inline bool mat2::Equal(const mat2& a) const
{
	return mat[0].Equal(a[0]) && mat[1].Equal(a[1]);
}

inline bool mat2::Equal(const mat2& a, f32 epsilon) const
{
	return mat[0].Equal(a[0], epsilon) && mat[1].Equal(a[1], epsilon);
}

inline mat2& mat2::Zero()
{
	memset(mat, 0, sizeof(mat2));
	return *this;
}

inline mat2& mat2::Identity()
{
	*this = IdentityMat2();
	return *this;
}

inline bool mat2::Identity(f32 epsilon) const
{
	return Equal(IdentityMat2(), epsilon);
}

inline bool mat2::Symmetric(f32 epsilon) const
{
	return Absf(mat[0][1] - mat[1][0]) < epsilon;
}

inline bool mat2::Diagonal(f32 epsilon) const
{
	return Absf(mat[0][1]) <= epsilon &&
		   Absf(mat[1][0]) <= epsilon;
}

inline f32 mat2::Trace() const
{
	return mat[0][0] + mat[1][1];
}

inline f32 mat2::Determinant() const
{
	return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

inline mat2 mat2::Transpose() const
{
	return mat2
	(
		mat[0][0], mat[1][0],
		mat[0][1], mat[1][1]
	);
}

inline mat2& mat2::TransposeSelf()
{
	Swap(mat[0][1], mat[1][0]);
	return *this;
}

inline mat2 mat2::Inverse() const
{
	mat2 invMat = *this;
	const bool res = invMat.InverseSelf();
	ASSERT(res);
	return invMat;
}

inline bool mat2::InverseSelf()
{
	f32 det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

	if (Absf(det) < gMatrixInvEpsilon)
	{
		return false;
	}

	f32 invDet = 1.0f / det;
	f32 xx = mat[0][0];

	mat[0][0] =   mat[1][1] * invDet;
	mat[0][1] = - mat[0][1] * invDet;
	mat[1][0] = - mat[1][0] * invDet;
	mat[1][1] =   xx * invDet;

	return true;
}

inline s32 mat2::Dimension() const
{
	return 4;
}

inline const f32* mat2::Ptr() const
{
	return mat[0].Ptr();
}

inline f32* mat2::Ptr()
{
	return mat[0].Ptr();
}

// Row-major matrix 3x3.
struct mat3
{
	vec3			mat[3];

					mat3();
	explicit		mat3(const vec3& x, const vec3& y, const vec3& z);
	explicit		mat3(f32 xx, f32 xy, f32 xz, f32 yx, f32 yy, f32 yz, f32 zx, f32 zy, f32 zz);
	explicit		mat3(const f32 src[3][3]);

	const vec3& 	operator[](s32 index) const;
	vec3& 			operator[](s32 index);
	mat3			operator-() const;
	mat3			operator+(const mat3& a) const;
	mat3			operator-(const mat3& a) const;
	mat3			operator*(const mat3& a) const;
	vec3			operator*(const vec3& vec) const;
	mat3			operator*(f32 a) const;
	mat3& 			operator+=(const mat3& a);
	mat3& 			operator-=(const mat3& a);
	mat3& 			operator*=(const mat3& a);
	mat3& 			operator*=(f32 a);

	bool			operator==(const mat3& a) const;
	bool			operator!=(const mat3& a) const;

	friend mat3		operator*(f32 a, const mat3& mat);
	friend vec3		operator*(const vec3& vec, const mat3& mat);
	friend vec3& 	operator*=(vec3& vec, const mat3& mat);

	bool			Equal(const mat3& a) const;
	bool			Equal(const mat3& a, f32 epsilon) const;

	mat3&			Zero();
	mat3&			Identity();
	bool			Identity(f32 epsilon = gMatrixEpsilon) const;
	bool			Symmetric(f32 epsilon = gMatrixEpsilon) const;
	bool			Diagonal(f32 epsilon = gMatrixEpsilon) const;
	bool			Rotated() const;

	f32				Trace() const;
	f32				Determinant() const;
	mat3			Transpose() const;
	mat3& 			TransposeSelf();
	mat3			Inverse() const;
	bool			InverseSelf();

	s32				Dimension() const;

	mat4			Mat4() const;

	const f32*		Ptr() const;
	f32*			Ptr();
};

inline mat3 IdentityMat3()
{
	return mat3(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1));
}

inline mat3::mat3()
{
}

inline mat3::mat3(const vec3& x, const vec3& y, const vec3& z)
{
	mat[0] = x;
	mat[1] = y;
	mat[2] = z;
}

inline mat3::mat3(f32 xx, f32 xy, f32 xz, f32 yx, f32 yy, f32 yz, f32 zx, f32 zy, f32 zz)
{
	mat[0][0] = xx; mat[0][1] = xy; mat[0][2] = xz;
	mat[1][0] = yx; mat[1][1] = yy; mat[1][2] = yz;
	mat[2][0] = zx; mat[2][1] = zy; mat[2][2] = zz;
}

inline mat3::mat3(const f32 src[3][3])
{
	memcpy(mat, src, 3 * 3 * sizeof(f32));
}

inline const vec3& mat3::operator[](s32 index) const
{
	return mat[index];
}

inline vec3& mat3::operator[](s32 index)
{
	return mat[index];
}

inline mat3 mat3::operator-() const
{
	return mat3
	(
		-mat[0][0], -mat[0][1], -mat[0][2],
		-mat[1][0], -mat[1][1], -mat[1][2],
		-mat[2][0], -mat[2][1], -mat[2][2]
	);
}

inline mat3 mat3::operator+(const mat3& a) const
{
	return mat3
	(
		mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2],
		mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2],
		mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2]
	);
}

inline mat3 mat3::operator-(const mat3& a) const
{
	return mat3
	(
		mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2],
		mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2],
		mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2]
	);
}

inline mat3 mat3::operator*(const mat3& a) const
{
	mat3 dst;
	f32* dstPtr		= reinterpret_cast<f32*>(&dst);
	const f32* ptr	= reinterpret_cast<const f32*>(this);
	const f32* aptr = reinterpret_cast<const f32*>(&a);

	for (s32 i = 0; i < 3; ++i)
	{
		for (s32 j = 0; j < 3; ++j)
		{
			*dstPtr = ptr[0] * aptr[0 * 3 + j] +
					  ptr[1] * aptr[1 * 3 + j] +
					  ptr[2] * aptr[2 * 3 + j];
			dstPtr++;
		}
		ptr += 3;
	}

	return dst;
}

inline vec3 mat3::operator*(const vec3& vec) const
{
	return vec3
	(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2]
	);
}

inline mat3 mat3::operator*(f32 a) const
{
	return mat3
	(
		mat[0][0] * a, mat[0][1] * a, mat[0][2] * a,
		mat[1][0] * a, mat[1][1] * a, mat[1][2] * a,
		mat[2][0] * a, mat[2][1] * a, mat[2][2] * a
	);
}

inline mat3& mat3::operator+=(const mat3& a)
{
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2];
	return *this;
}

inline mat3& mat3::operator-=(const mat3& a)
{
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2];
	return *this;
}

inline mat3& mat3::operator*=(const mat3& a)
{
	*this = *this * a;
	return *this;
}

inline mat3& mat3::operator*=(f32 a)
{
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a;
	return *this;
}

inline bool mat3::operator==(const mat3& a) const
{
	return Equal(a);
}

inline bool mat3::operator!=(const mat3& a) const
{
	return !(*this == a);
}

inline vec3 operator*(const vec3& vec, const mat3& mat)
{
	return mat * vec;
}

inline mat3 operator*(f32 a, const mat3& mat)
{
	return mat * a;
}

inline vec3& operator*=(vec3& vec, const mat3& mat)
{
	vec = mat * vec;
	return vec;
}

inline bool mat3::Equal(const mat3& a) const
{
	return mat[0].Equal(a[0]) &&
		   mat[1].Equal(a[1]) &&
		   mat[2].Equal(a[2]);
}

inline bool mat3::Equal(const mat3& a, f32 epsilon) const
{
	return mat[0].Equal(a[0], epsilon) &&
		   mat[1].Equal(a[1], epsilon) &&
		   mat[2].Equal(a[2], epsilon);
}

inline mat3& mat3::Zero()
{
	memset(mat, 0, sizeof(mat3));
	return *this;
}

inline mat3& mat3::Identity()
{
	*this = IdentityMat3();
	return *this;
}

inline bool mat3::Identity(f32 epsilon) const
{
	return Equal(IdentityMat3(), epsilon);
}

inline bool mat3::Symmetric(f32 epsilon) const
{
	return Absf(mat[0][1] - mat[1][0]) <= epsilon &&
	   	   Absf(mat[0][2] - mat[2][0]) <= epsilon &&
	   	   Absf(mat[1][2] - mat[2][1]) <= epsilon;
}

inline bool mat3::Diagonal(f32 epsilon) const
{
	return Absf(mat[0][1]) <= epsilon &&
		   Absf(mat[0][2]) <= epsilon &&
		   Absf(mat[1][0]) <= epsilon &&
		   Absf(mat[1][2]) <= epsilon &&
		   Absf(mat[2][0]) <= epsilon &&
		   Absf(mat[2][1]) <= epsilon;
}

inline bool mat3::Rotated() const
{
	return mat[0][1] != 0.0f || mat[0][2] != 0.0f ||
	   	   mat[1][0] != 0.0f || mat[1][2] != 0.0f ||
	   	   mat[2][0] != 0.0f || mat[2][1] != 0.0f;
}

inline f32 mat3::Trace() const
{
	return mat[0][0] + mat[1][1] + mat[2][2];
}

inline f32 mat3::Determinant() const
{
	// determinant_size_rows_cols

	const f32 det2_12_01 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
	const f32 det2_12_02 = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
	const f32 det2_12_12 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];

	return mat[0][0] * det2_12_12 - mat[0][1] * det2_12_02 + mat[0][2] * det2_12_01;
}

inline mat3 mat3::Transpose() const
{
	return mat3
	(
		mat[0][0], mat[1][0], mat[2][0],
		mat[0][1], mat[1][1], mat[2][1],
		mat[0][2], mat[1][2], mat[2][2]
	);
}

inline mat3& mat3::TransposeSelf()
{
	Swap(mat[0][1], mat[1][0]);
	Swap(mat[0][2], mat[2][0]);
	Swap(mat[1][2], mat[2][1]);
	return *this;
}

inline mat3 mat3::Inverse() const
{
	mat3 invMat = *this;
	const bool res = invMat.InverseSelf();
	ASSERT(res);
	return invMat;
}

inline s32 mat3::Dimension() const
{
	return 9;
}

inline const f32* mat3::Ptr() const
{
	return mat[0].Ptr();
}

inline f32* mat3::Ptr()
{
	return mat[0].Ptr();
}

// Row-major matrix 4x4.
struct mat4
{
	vec4			mat[4];

					mat4();
	explicit 		mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w);
	explicit 		mat4(f32 xx, f32 xy, f32 xz, f32 xw,
						 f32 yx, f32 yy, f32 yz, f32 yw,
						 f32 zx, f32 zy, f32 zz, f32 zw,
						 f32 wx, f32 wy, f32 wz, f32 ww);
	explicit		mat4(const mat3& rotation, const vec3& translation);
	explicit		mat4(const f32 src[4][4]);
	explicit		mat4(const f32* src);

	const vec4& 	operator[](s32 index) const;
	vec4& 			operator[](s32 index);
	mat4			operator+(const mat4& a) const;
	mat4			operator-(const mat4& a) const;
	mat4			operator*(const mat4& a) const;
	vec4			operator*(const vec4& vec) const;
	vec3			operator*(const vec3& vec) const;
	mat4			operator*(f32 a) const;
	mat4& 			operator+=(const mat4& a);
	mat4& 			operator-=(const mat4& a);
	mat4& 			operator*=(const mat4& a);
	mat4& 			operator*=(f32 a);

	bool			operator==(const mat4& a) const;
	bool			operator!=(const mat4& a) const;

	friend vec4		operator*(const vec4& vec, const mat4& mat);
	friend vec3		operator*(const vec3& vec, const mat4& mat);
	friend mat4		operator*(f32 a, const mat4& mat);
	friend vec4& 	operator*=(vec4& vec, const mat4& mat);
	friend vec3& 	operator*=(vec3& vec, const mat4& mat);

	bool			Equal(const mat4& a) const;
	bool			Equal(const mat4& a, f32 epsilon) const;

	mat4&			Zero();
	mat4&			Identity();
	bool			Identity(f32 epsilon = gMatrixEpsilon) const;
	bool			Symmetric(f32 epsilon = gMatrixEpsilon) const;
	bool			Diagonal(f32 epsilon = gMatrixEpsilon) const;
	bool			Rotated() const;

	f32				Trace() const;
	f32				Determinant() const;
	mat4			Transpose() const;
	mat4& 			TransposeSelf();
	mat4			Inverse() const;
	bool			InverseSelf();

	mat4&			Translate(const vec3& translation);
	mat4&			Rotate(const mat4& rotation);
	mat4&			Rotate(const quat& rotation);
	mat4&			Scale(const vec3& scale);

	s32				Dimension() const;

	const f32*		Ptr() const;
	f32*			Ptr();
};

inline mat4 mat3::Mat4() const
{
	return mat4
	(
		mat[0][0],	mat[0][1],	mat[0][2],	0.0f,
		mat[1][0],	mat[1][1],	mat[1][2],	0.0f,
		mat[2][0],	mat[2][1],	mat[2][2],	0.0f,
		0.0f,		0.0f,		0.0f,		1.0f
	);
}

inline mat4 IdentityMat4()
{
	return mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 1, 0), vec4(0, 0, 0, 1));
}

inline mat4::mat4()
{
}

inline mat4::mat4(const vec4& x, const vec4& y, const vec4& z, const vec4& w)
{
	mat[0] = x;
	mat[1] = y;
	mat[2] = z;
	mat[3] = w;
}

inline mat4::mat4(f32 xx, f32 xy, f32 xz, f32 xw,
					  f32 yx, f32 yy, f32 yz, f32 yw,
					  f32 zx, f32 zy, f32 zz, f32 zw,
					  f32 wx, f32 wy, f32 wz, f32 ww)
{
	mat[0][0] = xx; mat[0][1] = xy; mat[0][2] = xz; mat[0][3] = xw;
	mat[1][0] = yx; mat[1][1] = yy; mat[1][2] = yz; mat[1][3] = yw;
	mat[2][0] = zx; mat[2][1] = zy; mat[2][2] = zz; mat[2][3] = zw;
	mat[3][0] = wx; mat[3][1] = wy; mat[3][2] = wz; mat[3][3] = ww;
}

inline mat4::mat4(const mat3& rotation, const vec3& translation)
{
	mat[0][0] = rotation[0][0];
	mat[0][1] = rotation[0][1];
	mat[0][2] = rotation[0][2];
	mat[0][3] = translation[0];

	mat[1][0] = rotation[1][0];
	mat[1][1] = rotation[1][1];
	mat[1][2] = rotation[1][2];
	mat[1][3] = translation[1];

	mat[2][0] = rotation[2][0];
	mat[2][1] = rotation[2][1];
	mat[2][2] = rotation[2][2];
	mat[2][3] = translation[2];

	mat[3][0] = 0.0f;
	mat[3][1] = 0.0f;
	mat[3][2] = 0.0f;
	mat[3][3] = 1.0f;
}

inline mat4::mat4(const f32 src[4][4])
{
	memcpy(mat, src, 4 * 4 * sizeof(f32));
}

inline mat4::mat4(const f32* src)
{
	memcpy(mat, src, 4 * 4 * sizeof(f32));
}

inline const vec4& mat4::operator[](s32 index) const
{
	return mat[index];
}

inline vec4& mat4::operator[](s32 index)
{
	return mat[index];
}

inline mat4 mat4::operator+(const mat4& a) const
{
	return mat4
	(
		mat[0][0] + a[0][0], mat[0][1] + a[0][1], mat[0][2] + a[0][2], mat[0][3] + a[0][3],
		mat[1][0] + a[1][0], mat[1][1] + a[1][1], mat[1][2] + a[1][2], mat[1][3] + a[1][3],
		mat[2][0] + a[2][0], mat[2][1] + a[2][1], mat[2][2] + a[2][2], mat[2][3] + a[2][3],
		mat[3][0] + a[3][0], mat[3][1] + a[3][1], mat[3][2] + a[3][2], mat[3][3] + a[3][3]
	);
}

inline mat4 mat4::operator-(const mat4& a) const
{
	return mat4
	(
		mat[0][0] - a[0][0], mat[0][1] - a[0][1], mat[0][2] - a[0][2], mat[0][3] - a[0][3],
		mat[1][0] - a[1][0], mat[1][1] - a[1][1], mat[1][2] - a[1][2], mat[1][3] - a[1][3],
		mat[2][0] - a[2][0], mat[2][1] - a[2][1], mat[2][2] - a[2][2], mat[2][3] - a[2][3],
		mat[3][0] - a[3][0], mat[3][1] - a[3][1], mat[3][2] - a[3][2], mat[3][3] - a[3][3]
	);
}

inline mat4 mat4::operator*(const mat4& a) const
{
	mat4 dst;
	f32* dstPtr		= reinterpret_cast<f32*>(&dst);
	const f32* ptr	= reinterpret_cast<const f32*>(this);
	const f32* aptr = reinterpret_cast<const f32*>(&a);

	for (s32 i = 0; i < 4; ++i)
	{
		for (s32 j = 0; j < 4; ++j)
		{
			*dstPtr = ptr[0] * aptr[0 * 4 + j] +
					  ptr[1] * aptr[1 * 4 + j] +
					  ptr[2] * aptr[2 * 4 + j] +
					  ptr[3] * aptr[3 * 4 + j];
			dstPtr++;
		}
		ptr += 4;
	}

	return dst;
}

inline vec4 mat4::operator*(const vec4& vec) const
{
	return vec4
	(
		mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3],
		mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3],
		mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3],
		mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3])
	;
}

inline vec3 mat4::operator*(const vec3& vec) const
{
	const f32 scalar = mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3];

	if (scalar == 0.0f)
	{
		return vec3(0.0f, 0.0f, 0.0f);
	}

	if (scalar == 1.0f)
	{
		return vec3
		(
			mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3],
			mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3],
			mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3]
		);
	}

	const f32 invScalar = 1.0f / scalar;
	return vec3
	(
		(mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3]) * invScalar,
		(mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3]) * invScalar,
		(mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3]) * invScalar
	);
}

inline mat4 mat4::operator*(f32 a) const
{
	return mat4
	(
		mat[0][0] * a, mat[0][1] * a, mat[0][2] * a, mat[0][3] * a,
		mat[1][0] * a, mat[1][1] * a, mat[1][2] * a, mat[1][3] * a,
		mat[2][0] * a, mat[2][1] * a, mat[2][2] * a, mat[2][3] * a,
		mat[3][0] * a, mat[3][1] * a, mat[3][2] * a, mat[3][3] * a
	);
}

inline mat4& mat4::operator+=(const mat4& a)
{
	mat[0][0] += a[0][0]; mat[0][1] += a[0][1]; mat[0][2] += a[0][2]; mat[0][3] += a[0][3];
	mat[1][0] += a[1][0]; mat[1][1] += a[1][1]; mat[1][2] += a[1][2]; mat[1][3] += a[1][3];
	mat[2][0] += a[2][0]; mat[2][1] += a[2][1]; mat[2][2] += a[2][2]; mat[2][3] += a[2][3];
	mat[3][0] += a[3][0]; mat[3][1] += a[3][1]; mat[3][2] += a[3][2]; mat[3][3] += a[3][3];
	return *this;
}

inline mat4& mat4::operator-=(const mat4& a)
{
	mat[0][0] -= a[0][0]; mat[0][1] -= a[0][1]; mat[0][2] -= a[0][2]; mat[0][3] -= a[0][3];
	mat[1][0] -= a[1][0]; mat[1][1] -= a[1][1]; mat[1][2] -= a[1][2]; mat[1][3] -= a[1][3];
	mat[2][0] -= a[2][0]; mat[2][1] -= a[2][1]; mat[2][2] -= a[2][2]; mat[2][3] -= a[2][3];
	mat[3][0] -= a[3][0]; mat[3][1] -= a[3][1]; mat[3][2] -= a[3][2]; mat[3][3] -= a[3][3];
	return *this;
}

inline mat4& mat4::operator*=(const mat4& a)
{
	*this = *this * a;
	return *this;
}

inline mat4& mat4::operator*=(f32 a)
{
	mat[0][0] *= a; mat[0][1] *= a; mat[0][2] *= a; mat[0][3] *= a;
	mat[1][0] *= a; mat[1][1] *= a; mat[1][2] *= a; mat[1][3] *= a;
	mat[2][0] *= a; mat[2][1] *= a; mat[2][2] *= a; mat[2][3] *= a;
	mat[3][0] *= a; mat[3][1] *= a; mat[3][2] *= a; mat[3][3] *= a;
    return *this;
}

inline bool mat4::operator==(const mat4& a) const
{
	return Equal(a);
}

inline bool mat4::operator!=(const mat4& a) const
{
	return !(*this == a);
}

inline vec4 operator*(const vec4& vec, const mat4& mat)
{
	return mat * vec;
}

inline vec3 operator*(const vec3& vec, const mat4& mat)
{
	return mat * vec;
}

inline mat4 operator*(f32 a, const mat4& mat)
{
	return mat * a;
}

inline vec4& operator*=(vec4& vec, const mat4& mat)
{
	vec = mat * vec;
	return vec;
}

inline vec3& operator*=(vec3& vec, const mat4& mat)
{
	vec = mat * vec;
	return vec;
}

inline bool mat4::Equal(const mat4& a) const
{
	return mat[0].Equal(a[0]) &&
		   mat[1].Equal(a[1]) &&
		   mat[2].Equal(a[2]) &&
		   mat[3].Equal(a[3]);
}

inline bool mat4::Equal(const mat4& a, f32 epsilon) const
{
	return mat[0].Equal(a[0], epsilon) &&
	       mat[1].Equal(a[1], epsilon) &&
	       mat[2].Equal(a[2], epsilon) &&
	       mat[3].Equal(a[3], epsilon);
}

inline mat4& mat4::Zero()
{
	memset(mat, 0, sizeof(mat4));
	return *this;
}

inline mat4& mat4::Identity()
{
	*this = IdentityMat4();
	return *this;
}

inline bool mat4::Identity(f32 epsilon) const
{
	return Equal(IdentityMat4(), epsilon);
}

inline bool mat4::Symmetric(f32 epsilon) const
{
	for (s32 i = 1; i < 4; ++i)
	{
		for (s32 j = 0; j < i; ++j)
		{
			if (Absf(mat[i][j] - mat[j][i]) > epsilon)
			{
				return false;
			}
		}
	}

	return true;
}

inline bool mat4::Diagonal(f32 epsilon) const
{
	for (s32 i = 0; i < 4; ++i)
	{
		for (s32 j = 0; j < 4; ++j)
		{
			if (i != j && Absf(mat[i][j]) > epsilon)
			{
				return false;
			}
		}
	}

	return true;
}

inline bool mat4::Rotated() const
{
	return mat[0][1] != 0.0f || mat[0][2] != 0.0f ||
		   mat[1][0] != 0.0f || mat[1][2] != 0.0f ||
		   mat[2][0] != 0.0f || mat[2][1] != 0.0f;
}

inline f32 mat4::Trace() const
{
	return mat[0][0] + mat[1][1] + mat[2][2] + mat[3][3];
}

inline mat4 mat4::Transpose() const
{
	mat4 transpose;

	for(s32 i = 0; i < 4; ++i)
	{
		for(s32 j = 0; j < 4; ++j)
		{
			transpose[i][j] = mat[j][i];
		}
	}

	return transpose;
}

inline mat4& mat4::TransposeSelf()
{
	for(s32 i = 0; i < 4; ++i)
	{
		for(s32 j = i + 1; j < 4; ++j)
		{
			Swap(mat[i][j], mat[j][i]);
		}
	}

	return *this;
}

inline mat4 mat4::Inverse() const
{
	mat4 invMat = *this;
	const bool res = invMat.InverseSelf();
	ASSERT(res);
	return invMat;
}

inline mat4& mat4::Translate(const vec3& translation)
{
	mat[3][0] = translation.x;
	mat[3][1] = translation.y;
	mat[3][2] = translation.z;
	return *this;
}

inline mat4& mat4::Scale(const vec3& scale)
{
	mat[0][0] = scale.x;
	mat[1][1] = scale.y;
	mat[2][2] = scale.z;
	return *this;
}

inline s32 mat4::Dimension() const
{
	return 16;
}

inline const f32 *mat4::Ptr() const
{
	return mat[0].Ptr();
}

inline f32 *mat4::Ptr()
{
	return mat[0].Ptr();
}
