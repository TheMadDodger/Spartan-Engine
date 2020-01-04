#include "stdafx.h"
#include "MathHelpers.h"
#include "ContentManager.h"

using namespace Math;

Math::Vector2::Vector2(const Vector3& vec3): x(vec3.x), y(vec3.y) {}

float Vector2::Length()
{
	return sqrt((x * x) + (y * y));
}

Vector2 Vector2::operator+(const Vector2 &other)
{
	Vector2 result;
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}

bool Math::Vector2::operator==(const Vector2 & other)
{
	return x == other.x && y == other.y;
}

bool Math::Vector2::operator!=(const Vector2 & other)
{
	return x != other.x || y != other.y;
}

void Math::Vector2::operator+=(const Vector2 &other)
{
	x += other.x;
	y += other.y;
}

Vector2 Vector2::operator-(const Vector2 &other)
{
	Vector2 result;
	result.x = x - other.x;
	result.y = y - other.y;
	return result;
}

Vector2 Vector2::operator*(const Vector2 & other)
{
	Vector2 result;
	result.x = x * other.x;
	result.y = y * other.y;
	return result;
}

Vector2 Vector2::operator*(const IntVector2 &other)
{
	Vector2 result;
	result.x = x * (float)other.x;
	result.y = y * (float)other.y;
	return result;
}

Vector2 Vector2::operator*(float factor)
{
	Vector2 result;
	result.x = x * factor;
	result.y = y * factor;
	return result;
}

void Math::Vector2::operator*=(float factor)
{
	x *= factor;
	y *= factor;
}

Vector2 Math::Vector2::operator/(float factor)
{
	Vector2 result;
	result.x = x / factor;
	result.y = y / factor;
	return result;
}

Vector2 Math::Vector2::operator/(const Vector2 & other)
{
	Vector2 result;
	result.x = x / other.x;
	result.y = y / other.y;
	return result;
}

float Vector2::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	return length;
}

Vector2 Vector2::Normalized()
{
	Vector2 result;
	result.x = x;
	result.y = y;
	result.Normalize();
	return result;
}

Vector2 Math::Vector2::Lerp(const Vector2 &a, const Vector2 &b, float t)
{
	Vector2 result;
	result.x = Math::Lerp(a.x, b.x, t);
	result.y = Math::Lerp(a.y, b.y, t);
	return result;
}

IntVector2 Math::IntVector2::operator+(const IntVector2 &other)
{
	IntVector2 result = IntVector2();
	result.x = x + other.x;
	result.y = y + other.y;
	return result;
}

IntVector2 Math::IntVector2::operator-(const IntVector2 &other)
{
	IntVector2 result = IntVector2();
	result.x = x - other.x;
	result.y = y - other.y;
	return result;
}

IntVector2 Math::IntVector2::operator*(const IntVector2 &other)
{
	IntVector2 result = IntVector2();
	result.x = x * other.x;
	result.y = y * other.y;
	return result;
}

Math::Vector3::Vector3(const Vector4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}

float Vector3::Length()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	Vector3 result;
	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z + other.z;
	return result;
}

Vector3 Math::Vector3::operator+(const Vector2& other)
{
	Vector3 result;
	result.x = x + other.x;
	result.y = y + other.y;
	result.z = z;
	return result;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	Vector3 result;
	result.x = x - other.x;
	result.y = y - other.y;
	result.z = z - other.z;
	return result;
}

Vector3 Vector3::operator*(const Vector3 & other)
{
	Vector3 result;
	result.x = x * other.x;
	result.y = y * other.y;
	result.z = z * other.z;
	return result;
}

Vector3 Vector3::operator*(float factor)
{
	Vector3 result;
	result.x = x * factor;
	result.y = y * factor;
	result.z = z * factor;
	return result;
}

Vector3 Math::Vector3::operator/(float factor)
{
	Vector3 result;
	result.x = x / factor;
	result.y = y / factor;
	result.z = z / factor;
	return result;
}

float Vector3::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	return length;
}

Vector3 Vector3::Normalized() const
{
	Vector3 result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.Normalize();
	return result;
}

Vector3 Math::Vector3::Rotate(const Vector3& vec, Quaternion& rotation)
{
	Quaternion conjugate = rotation.Conjugate();
	Quaternion w = rotation * vec * conjugate;
	return Vector3(w.x, w.y, w.z);
}

Vector3 Math::Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	Vector3 result;
	result.x = Math::Lerp(a.x, b.x, t);
	result.y = Math::Lerp(a.y, b.y, t);
	result.z = Math::Lerp(a.z, b.z, t);
	return result;
}

Matrix3X3 Matrix3X3::operator*(const Matrix3X3 & other)
{
	auto result = CreateIdentityMatrix();

	// First row
	result.m[0][0] = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1] + m[2][0] * other.m[0][2];
	result.m[1][0] = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1] + m[2][0] * other.m[1][2];
	result.m[2][0] = m[0][0] * other.m[2][0] + m[1][0] * other.m[2][1] + m[2][0] * other.m[2][2];

	// Second row
	result.m[0][1] = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1] + m[2][1] * other.m[0][2];
	result.m[1][1] = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1] + m[2][1] * other.m[1][2];
	result.m[2][1] = m[0][1] * other.m[2][0] + m[1][1] * other.m[2][1] + m[2][1] * other.m[2][2];

	// Third row
	result.m[0][2] = m[0][2] * other.m[0][0] + m[1][2] * other.m[0][1] + m[2][2] * other.m[0][2];
	result.m[1][2] = m[0][2] * other.m[1][0] + m[1][2] * other.m[1][1] + m[2][2] * other.m[1][2];
	result.m[2][2] = m[0][2] * other.m[2][0] + m[1][2] * other.m[2][1] + m[2][2] * other.m[2][2];

	return result;
}

Vector3 Matrix3X3::operator*(const Vector3 &other)
{
	Vector3 result = Vector3::Zero();

	result.x = m[0][0] * other.x + m[1][0] * other.y + m[2][0] * other.z;
	result.y = m[0][1] * other.x + m[1][1] * other.y + m[2][1] * other.z;
	result.z = m[0][2] * other.x + m[1][2] * other.y + m[2][2] * other.z;

	return result;
}

Matrix3X3 Math::Matrix3X3::operator*(float factor)
{
	Matrix3X3 result = Matrix3X3::CreateIdentityMatrix();

	for (size_t x = 0; x < 3; ++x)
		for (size_t y = 0; y < 3; ++y)
			result.m[x][y] = m[x][y] * factor;

	return result;
}

Matrix3X3 Math::Matrix3X3::operator+(const Matrix3X3 &other)
{
	Matrix3X3 result = Matrix3X3::CreateIdentityMatrix();

	for (size_t x = 0; x < 3; ++x)
		for (size_t y = 0; y < 3; ++y)
			result.m[x][y] = m[x][y] + other.m[x][y];

	return result;
}

const Vector2 Math::Matrix3X3::ExtraxtTranslation() const
{
	return Vector2(m[2][0], m[2][1]);
}

const Vector3 Math::Matrix3X3::ExtraxtRotation() const
{
	return Vector3(0, 0, atan2(m[0][1], m[0][0]));
}

const Vector2 Math::Matrix3X3::ExtraxtScale() const
{
	Vector2 xVec = Vector2();
	Vector2 yVec = Vector2();

	xVec.x = m[0][0];
	xVec.y = m[0][1];

	yVec.x = m[1][0];
	yVec.y = m[1][1];

	//Vector2 scale = Vector2(xVec.Length(), yVec.Length());

	return Vector2(xVec.Length(), yVec.Length());
}

Matrix3X3 Matrix3X3::CreateIdentityMatrix()
{
	auto matrix = Matrix3X3(1.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 1.0f);
	return matrix;
}

Matrix3X3 Matrix3X3::CreateTranslationMatrix(const Vector2 &translation)
{
	auto matrix = CreateIdentityMatrix();
	matrix.m[2][0] = translation.x;
	matrix.m[2][1] = translation.y;
	return matrix;
}

Matrix3X3 Math::Matrix3X3::CreateRotationMatrix(const Vector3 &rotation)
{
	auto matRot = Matrix3X3(cos(rotation.z), -sin(rotation.z), 0,
							sin(rotation.z),  cos(rotation.z), 0,
							0,				  0,			   1);

	return matRot;
}

Matrix3X3 Matrix3X3::CreateScalingMatrix(const Vector2 &scale)
{
	auto matScale = CreateIdentityMatrix();
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;

	return matScale;
}

Matrix3X3 Matrix3X3::CreateScaleRotationTranslationMatrix(const Vector2 &translation, const Vector3 &rotation, const Vector2 &scale)
{
	Matrix3X3 matTrans = Matrix3X3::CreateTranslationMatrix(translation);
	Matrix3X3 matRot = Matrix3X3::CreateRotationMatrix(rotation);
	Matrix3X3 matScale = Matrix3X3::CreateScalingMatrix(scale);

	Matrix3X3 matScaleRot = matRot * matScale;
	Matrix3X3 matScaleRotTrans = matTrans * matScaleRot;

	return matScaleRotTrans;
}

Matrix3X3 Math::Matrix3X3::Inverse() const
{
	/// Calculate the inverse matrix
	// Decompose matrix
	auto trans = ExtraxtTranslation();
	auto scale = ExtraxtScale();
	auto rot = ExtraxtRotation();

	if (scale.x == 0 || scale.y == 0)
	{
		Utilities::Debug::LogError("Math::Matrix3X3::Inverse > Scale is 0");
	}

	// Inverse each component and turn into a matrix
	trans = trans * -1;
	rot = rot * -1;
	scale.x = 1.0f / scale.x;
	scale.y = 1.0f / scale.y;

	auto transMat = Matrix3X3::CreateTranslationMatrix(trans);
	auto rotMat = Matrix3X3::CreateRotationMatrix(rot);
	auto scaleMat = Matrix3X3::CreateScalingMatrix(scale);

	// Multiply matrices in oposite order
	auto scaleRotMat = scaleMat * rotMat;
	auto scaleRotTransMat = scaleRotMat * transMat;
	return scaleRotTransMat;
}

Color Color::Lerp(const Color &a, const Color &b, float t)
{
	Color result;
	result.r = Math::Lerp(a.r, b.r, t);
	result.g = Math::Lerp(a.g, b.g, t);
	result.b = Math::Lerp(a.b, b.b, t);
	result.a = Math::Lerp(a.a, b.a, t);
	return result;
}

void Color::operator*=(float f)
{
	r *= f;
	g *= f;
	b *= f;
	a *= f;
}

Color Color::operator*(float f)
{
	Color result(r, g, b, a);
	result *= f;
	return result;
}

Color Color::operator-(const Color &other)
{
	Color result;
	result.r = r - other.r;
	result.g = g - other.g;
	result.b = b - other.b;
	result.a = a - other.a;
	return result;
}

Color Math::Color::operator+(const Color & other)
{
	Color result;
	result.r = r + other.r;
	result.g = g + other.g;
	result.b = b + other.b;
	result.a = a + other.a;
	return result;
}

bool Math::Color::operator==(const Color & other)
{
	return (r == other.r && g == other.g && b == other.b && a == other.a);
}

bool Math::Color::operator!=(const Color & other)
{
	return (r != other.r || g != other.g || b != other.b || a != other.a);;
}








Matrix4X4 Math::Matrix4X4::operator*(const Matrix4X4& other)
{
	auto result = CreateIdentityMatrix();

	// First row
	result.m[0][0] = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1] + m[2][0] * other.m[0][2] + m[3][0] * other.m[0][3];
	result.m[1][0] = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1] + m[2][0] * other.m[1][2] + m[3][0] * other.m[1][3];
	result.m[2][0] = m[0][0] * other.m[2][0] + m[1][0] * other.m[2][1] + m[2][0] * other.m[2][2] + m[3][0] * other.m[2][3];
	result.m[3][0] = m[0][0] * other.m[3][0] + m[1][0] * other.m[3][1] + m[2][0] * other.m[3][2] + m[3][0] * other.m[3][3];

	// Second row
	result.m[0][1] = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1] + m[2][1] * other.m[0][2] + m[3][1] * other.m[0][3];
	result.m[1][1] = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1] + m[2][1] * other.m[1][2] + m[3][1] * other.m[1][3];
	result.m[2][1] = m[0][1] * other.m[2][0] + m[1][1] * other.m[2][1] + m[2][1] * other.m[2][2] + m[3][1] * other.m[2][3];
	result.m[3][1] = m[0][1] * other.m[3][0] + m[1][1] * other.m[3][1] + m[2][1] * other.m[3][2] + m[3][1] * other.m[3][3];

	// Third row
	result.m[0][2] = m[0][2] * other.m[0][0] + m[1][2] * other.m[0][1] + m[2][2] * other.m[0][2] + m[3][2] * other.m[0][3];
	result.m[1][2] = m[0][2] * other.m[1][0] + m[1][2] * other.m[1][1] + m[2][2] * other.m[1][2] + m[3][2] * other.m[1][3];
	result.m[2][2] = m[0][2] * other.m[2][0] + m[1][2] * other.m[2][1] + m[2][2] * other.m[2][2] + m[3][2] * other.m[2][3];
	result.m[3][2] = m[0][2] * other.m[3][0] + m[1][2] * other.m[3][1] + m[2][2] * other.m[3][2] + m[3][2] * other.m[3][3];

	// Fourth row
	result.m[0][3] = m[0][3] * other.m[0][0] + m[1][3] * other.m[0][1] + m[2][3] * other.m[0][2] + m[3][3] * other.m[0][3];
	result.m[1][3] = m[0][3] * other.m[1][0] + m[1][3] * other.m[1][1] + m[2][3] * other.m[1][2] + m[3][3] * other.m[1][3];
	result.m[2][3] = m[0][3] * other.m[2][0] + m[1][3] * other.m[2][1] + m[2][3] * other.m[2][2] + m[3][3] * other.m[2][3];
	result.m[3][3] = m[0][3] * other.m[3][0] + m[1][3] * other.m[3][1] + m[2][3] * other.m[3][2] + m[3][3] * other.m[3][3];

	return result;
}

Vector4 Math::Matrix4X4::operator*(const Vector3& other)
{
	Vector4 result = Vector4(other, 1.0f);

	result.x = m[0][0] * other.x + m[1][0] * other.y + m[2][0] * other.z + m[3][0] * 1.0f;
	result.y = m[0][1] * other.x + m[1][1] * other.y + m[2][1] * other.z + m[3][1] * 1.0f;
	result.z = m[0][2] * other.x + m[1][2] * other.y + m[2][2] * other.z + m[3][2] * 1.0f;
	result.w = m[0][3] * other.x + m[1][3] * other.y + m[2][3] * other.z + m[3][3] * 1.0f;

	return result;
}

Matrix4X4 Math::Matrix4X4::operator*(float factor)
{
	Matrix4X4 result = Matrix4X4::CreateIdentityMatrix();

	for (size_t x = 0; x < 4; ++x)
		for (size_t y = 0; y < 4; ++y)
			result.m[x][y] = m[x][y] * factor;

	return result;
}

Matrix4X4 Math::Matrix4X4::operator+(const Matrix4X4& other)
{
	Matrix4X4 result = Matrix4X4::CreateIdentityMatrix();

	for (size_t x = 0; x < 4; ++x)
		for (size_t y = 0; y < 4; ++y)
			result.m[x][y] = m[x][y] + other.m[x][y];

	return result;
}

const Vector3 Math::Matrix4X4::ExtraxtTranslation() const
{
	return Vector3(m[3][0], m[3][1], m[3][2]);
}

const Vector3 Math::Matrix4X4::ExtraxtRotation() const
{
	return Vector3();
	//return Vector3(0, 0, atan2(m[0][1], m[0][0]));
}

const Vector3 Math::Matrix4X4::ExtraxtScale() const
{
	Vector3 xVec = Vector3();
	Vector3 yVec = Vector3();
	Vector3 zVec = Vector3();

	xVec.x = m[0][0];
	xVec.y = m[0][1];
	xVec.z = m[0][2];

	yVec.x = m[1][0];
	yVec.y = m[1][1];
	yVec.z = m[1][2];

	zVec.x = m[2][0];
	zVec.y = m[2][1];
	zVec.z = m[2][2];

	return Vector3(xVec.Length(), yVec.Length(), zVec.Length());
}

Matrix4X4 Matrix4X4::CreateIdentityMatrix()
{
	auto matrix = Matrix4X4(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
	return matrix;
}

Matrix4X4 Matrix4X4::CreateTranslationMatrix(const Vector3& translation)
{
	auto matrix = CreateIdentityMatrix();
	matrix.m[3][0] = translation.x;
	matrix.m[3][1] = translation.y;
	matrix.m[3][2] = translation.z;
	return matrix;
}

Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Vector3& rotation)
{
	return CreateRotationMatrix(Quaternion::Euler(rotation));
}

Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Quaternion& rotation)
{
	return CreateRotationMatrix(rotation.GetForward(), rotation.GetUp(), rotation.GetRight());
}

Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Vector3& forward, const Vector3& up)
{
	Vector3 f = forward.Normalized();
	Vector3 r = up.Normalized();
	Vector3 u = Cross(f, r);

	return CreateRotationMatrix(f, u, r);
}

Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Vector3& forward, const Vector3& up, const Vector3& right)
{
	Matrix4X4 rotation = CreateIdentityMatrix();
	rotation.m[0][0] = right.x;		rotation.m[1][0] = right.y;		rotation.m[2][0] = right.z;		rotation.m[3][0] = 0;
	rotation.m[0][1] = up.x;		rotation.m[1][1] = up.y;		rotation.m[2][1] = up.z;		rotation.m[3][1] = 0;
	rotation.m[0][2] = forward.x;	rotation.m[1][2] = forward.y;	rotation.m[2][2] = forward.z;	rotation.m[3][2] = 0;
	rotation.m[0][3] = 0;			rotation.m[1][3] = 0;			rotation.m[2][3] = 0;			rotation.m[3][3] = 1;
	return rotation;
}

Matrix4X4 Matrix4X4::CreateScalingMatrix(const Vector3& scale)
{
	auto matScale = CreateIdentityMatrix();
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;

	return matScale;
}

Matrix4X4 Matrix4X4::CreateScaleRotationTranslationMatrix(const Vector3& translation, const Vector3& rotation, const Vector3& scale)
{
	Matrix4X4 matTrans = Matrix4X4::CreateTranslationMatrix(translation);
	Matrix4X4 matRot = Matrix4X4::CreateRotationMatrix(rotation);
	Matrix4X4 matScale = Matrix4X4::CreateScalingMatrix(scale);

	Matrix4X4 matScaleRot = matRot * matScale;
	Matrix4X4 matScaleRotTrans = matTrans * matScaleRot;

	return matScaleRotTrans;
}

Matrix4X4 Math::Matrix4X4::CreateScaleRotationTranslationMatrix(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
{
	Matrix4X4 matTrans = Matrix4X4::CreateTranslationMatrix(translation);
	Matrix4X4 matRot = Matrix4X4::CreateRotationMatrix(rotation);
	Matrix4X4 matScale = Matrix4X4::CreateScalingMatrix(scale);

	Matrix4X4 matScaleRot = matRot * matScale;
	Matrix4X4 matScaleRotTrans = matTrans * matScaleRot;

	return matScaleRotTrans;
}

Matrix4X4 Math::Matrix4X4::Inverse() const
{
	/// Calculate the inverse matrix
	// Decompose matrix
	auto trans = ExtraxtTranslation();
	auto scale = ExtraxtScale();
	auto rot = ExtraxtRotation();

	if (scale.x == 0 || scale.y == 0 || scale.z == 0)
	{
		Utilities::Debug::LogError("Math::Matrix3X3::Inverse > Scale is 0");
	}

	// Inverse each component and turn into a matrix
	trans = trans * -1;
	rot = rot * -1;
	scale.x = 1.0f / scale.x;
	scale.y = 1.0f / scale.y;
	scale.z = 1.0f / scale.z;

	auto transMat = Matrix4X4::CreateTranslationMatrix(trans);
	auto rotMat = Matrix4X4::CreateRotationMatrix(rot);
	auto scaleMat = Matrix4X4::CreateScalingMatrix(scale);

	// Multiply matrices in oposite order
	auto scaleRotMat = scaleMat * rotMat;
	auto scaleRotTransMat = scaleRotMat * transMat;
	return scaleRotTransMat;
}

Math::Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

Math::Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

float Math::Quaternion::Length()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

float Math::Quaternion::Normalize()
{
	float length = Length();
	x /= length;
	y /= length;
	z /= length;
	w /= length;
	return length;
}

Quaternion Math::Quaternion::Normalized() const
{
	Quaternion result = Quaternion(x, y, z, w);
	result.Normalize();
	return result;
}

Quaternion Math::Quaternion::Conjugate() const
{
	Quaternion result = Quaternion(-x, -y, -z, w);
	return result;
}

Quaternion Math::Quaternion::operator*(const Quaternion& other)
{
	Quaternion result = Quaternion();
	result.w = w * other.w - x * other.x - y * other.y - z * other.z;
	result.x = x * other.w + w * other.x + y * other.z - z * other.y;
	result.y = y * other.w + w * other.y + z * other.x - x * other.z;
	result.z = z * other.w + w * other.z + x * other.y - y * other.x;
	return result;
}

Quaternion Math::Quaternion::operator*(const Vector3& other)
{
	Quaternion result = Quaternion();
	result.w = -x * other.x - y * other.y - z * other.z;
	result.x = w * other.x + y * other.z - z * other.y;
	result.y = w * other.y + z * other.x - x * other.z;
	result.z = w * other.z + x * other.y - y * other.x;
	return result;
}

Quaternion Math::Quaternion::operator-(const Quaternion &other)
{
	return Quaternion(x - other.x, y - other.y, z - other.z, w - other.w);
}

Quaternion Math::Quaternion::operator+(const Quaternion& other)
{
	return Quaternion(x + other.x, y + other.y, z + other.z, w + other.w);
}

Quaternion Math::Quaternion::operator*(float f)
{
	return Quaternion(x * f, y * f, z * f, w * f);
}

Quaternion Math::Quaternion::Multiply(const Quaternion& other) const
{
	Quaternion result = Quaternion();
	result.w = w * other.w - x * other.x - y * other.y - z * other.z;
	result.x = x * other.w + w * other.x + y * other.z - z * other.y;
	result.y = y * other.w + w * other.y + z * other.x - x * other.z;
	result.z = z * other.w + w * other.z + x * other.y - y * other.x;
	return result;
}

Quaternion Math::Quaternion::Multiply(const Vector3& vec) const
{
	Quaternion result = Quaternion();
	result.w = -x * vec.x - y * vec.y - z * vec.z;
	result.x = w * vec.x + y * vec.z - z * vec.y;
	result.y = w * vec.y + z * vec.x - x * vec.z;
	result.z = w * vec.z + x * vec.y - y * vec.x;
	return result;
}

Vector3 Math::Quaternion::GetForward() const
{
	return Rotate(Vector3(0, 0, 1));
}

Vector3 Math::Quaternion::GetBack() const
{
	return Rotate(Vector3(0, 0, -1));
}

Vector3 Math::Quaternion::GetUp() const
{
	return Rotate(Vector3(0, 1, 0));
}

Vector3 Math::Quaternion::GetDown() const
{
	return Rotate(Vector3(0, -1, 0));
}

Vector3 Math::Quaternion::GetLeft() const
{
	return Rotate(Vector3(-1, 0, 0));
}

Vector3 Math::Quaternion::GetRight() const
{
	return Rotate(Vector3(1, 0, 0));
}

Quaternion Math::Quaternion::Euler(const Vector3& eulerAngles)
{
	return Quaternion();
}

Quaternion Math::Quaternion::Euler(float x, float y, float z)
{
	return Euler(Vector3(x, y, z));
}

Quaternion Math::Quaternion::Multiply(const Quaternion& q1, const Quaternion& q2)
{
	return (Quaternion&)q1 * q2;
}

Vector3 Math::Quaternion::Rotate(const Vector3& toRotate) const
{
	Quaternion conjugate = Conjugate();
	Quaternion w = Multiply(toRotate) * conjugate;
	return Vector3(w.x, w.y, w.z);
}
