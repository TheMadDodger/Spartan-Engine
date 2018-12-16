#include "stdafx.h"
#include "MathHelpers.h"
#include "ContentManager.h"

using namespace Math;

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

Vector2 Vector2::operator*(float factor)
{
	Vector2 result;
	result.x = x * factor;
	result.y = y * factor;
	return result;
}

Vector2 Math::Vector2::operator/(float factor)
{
	Vector2 result;
	result.x = x / factor;
	result.y = y / factor;
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

Vector3 Vector3::Normalized()
{
	Vector3 result;
	result.x = x;
	result.y = y;
	result.z = z;
	result.Normalize();
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
