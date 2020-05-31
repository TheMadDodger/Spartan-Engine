#include "stdafx.h"
#include "MathHelpers.h"
#include "ContentManager.h"

namespace SpartanEngine
{
	namespace Math
	{
		Math::Vector2::Vector2(const Vector3& vec3): x(vec3.x), y(vec3.y) {}

		float Vector2::Length()
		{
			return sqrt((x * x) + (y * y));
		}

		Vector2 Vector2::operator+(const Vector2 &other) const
		{
			Vector2 result;
			result.x = x + other.x;
			result.y = y + other.y;
			return result;
		}

		bool Math::Vector2::operator==(const Vector2 & other) const
		{
			return x == other.x && y == other.y;
		}

		bool Math::Vector2::operator!=(const Vector2 & other) const
		{
			return x != other.x || y != other.y;
		}

		void Math::Vector2::operator+=(const Vector2 &other)
		{
			x += other.x;
			y += other.y;
		}

		Vector2 Vector2::operator-(const Vector2 &other) const
		{
			Vector2 result;
			result.x = x - other.x;
			result.y = y - other.y;
			return result;
		}

		Vector2 Vector2::operator*(const Vector2 & other) const
		{
			Vector2 result;
			result.x = x * other.x;
			result.y = y * other.y;
			return result;
		}

		Vector2 Vector2::operator*(const IntVector2 &other) const
		{
			Vector2 result;
			result.x = x * (float)other.x;
			result.y = y * (float)other.y;
			return result;
		}

		Vector2 Vector2::operator*(float factor) const
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

		Vector2 Math::Vector2::operator/(float factor) const
		{
			Vector2 result;
			result.x = x / factor;
			result.y = y / factor;
			return result;
		}

		Vector2 Math::Vector2::operator/(const Vector2 & other) const
		{
			Vector2 result;
			result.x = x / other.x;
			result.y = y / other.y;
			return result;
		}

		float Vector2::Normalize()
		{
			float length = Length();
			if (length == 0.0f) return 0.0f;
			x /= length;
			y /= length;
			return length;
		}

		Vector2 Vector2::Normalized() const
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

		bool Math::IntVector2::operator==(const IntVector2& other) const
		{
			return (x == other.x && y == other.y);
		}

		bool IntVector2::operator!=(const IntVector2& other) const
		{
			return !(x == other.x && y == other.y);
		}

		Math::Vector3::Vector3(const Vector4& vec4) : x(vec4.x), y(vec4.y), z(vec4.z) {}

		float Vector3::Length()
		{
			return sqrt((x * x) + (y * y) + (z * z));
		}

		Vector3 Vector3::operator+(const Vector3 & other) const
		{
			Vector3 result;
			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z + other.z;
			return result;
		}

		Vector3 Math::Vector3::operator+(const Vector2& other) const
		{
			Vector3 result;
			result.x = x + other.x;
			result.y = y + other.y;
			result.z = z;
			return result;
		}

		Vector3 Vector3::operator-(const Vector3 & other) const
		{
			Vector3 result;
			result.x = x - other.x;
			result.y = y - other.y;
			result.z = z - other.z;
			return result;
		}

		Vector3 Vector3::operator*(const Vector3 & other) const
		{
			Vector3 result;
			result.x = x * other.x;
			result.y = y * other.y;
			result.z = z * other.z;
			return result;
		}

		Vector3 Vector3::operator*(float factor) const
		{
			Vector3 result;
			result.x = x * factor;
			result.y = y * factor;
			result.z = z * factor;
			return result;
		}

		Vector3 Math::Vector3::operator/(float factor) const
		{
			Vector3 result;
			result.x = x / factor;
			result.y = y / factor;
			result.z = z / factor;
			return result;
		}

		Vector3 Math::Vector3::operator/(const Vector3& other) const
		{
			Vector3 result;
			result.x = x / other.x;
			result.y = y / other.y;
			result.z = z / other.z;
			return result;
		}

		bool Math::Vector3::operator==(const Vector3& other) const
		{
			if (x != other.x) return false;
			if (y != other.y) return false;
			if (z != other.z) return false;
			return true;
		}

		bool Math::Vector3::operator!=(const Vector3& other) const
		{
			bool isEqual = operator==(other);
			return !isEqual;
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

		Math::Matrix3X3::Matrix3X3(const Matrix4X4& mat4) : Matrix3X3(mat4.m[0][0], mat4.m[0][1], mat4.m[0][2],
																	  mat4.m[1][0], mat4.m[1][1], mat4.m[1][2],
																	  mat4.m[2][0], mat4.m[2][1], mat4.m[2][2])
		{

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

		Vector3 Math::Color::rgb()
		{
			return Vector3(r, g, b);
		}

		Matrix4X4 Math::Matrix4X4::operator*(const Matrix4X4& other)
		{
			Matrix4X4 result = Matrix4X4();

			/// THESE CALCULATIONS ARE CORRECT
			/// YOU ALREADY TRIPPLE CHECKED THEM
			/// PLS STOP DOUBTING THEM K THX
			for (size_t row = 0; row < 4; ++row)
			{
				for (size_t col = 0; col < 4; ++col)
				{
					for (size_t row2 = 0; row2 < 4; ++row2)
					{
						result.m[row][col] += m[row][row2] * other.m[row2][col];
					}
				}
			}

			/*Vector4 row1 = Row(0);
			Vector4 row2 = Row(1);
			Vector4 row3 = Row(2);
			Vector4 row4 = Row(3);

			Vector4 col1 = other.Col(0);
			Vector4 col2 = other.Col(1);
			Vector4 col3 = other.Col(2);
			Vector4 col4 = other.Col(3);

			result.m[0][0] = Dot(row1, col1); result.m[0][1] = Dot(row1, col2); result.m[0][2] = Dot(row1, col3); result.m[0][3] = Dot(row1, col4);
			result.m[1][0] = Dot(row2, col1); result.m[1][1] = Dot(row2, col2); result.m[1][2] = Dot(row2, col3); result.m[1][3] = Dot(row2, col4);
			result.m[2][0] = Dot(row3, col1); result.m[2][1] = Dot(row3, col2); result.m[2][2] = Dot(row3, col3); result.m[2][3] = Dot(row3, col4);
			result.m[3][0] = Dot(row4, col1); result.m[3][1] = Dot(row4, col2); result.m[3][2] = Dot(row4, col3); result.m[3][3] = Dot(row4, col4);*/

			////First row
			//result.m[0][0] = m[0][0] * other.m[0][0] + m[1][0] * other.m[0][1] + m[2][0] * other.m[0][2] + m[3][0] * other.m[0][3];
			//result.m[1][0] = m[0][0] * other.m[1][0] + m[1][0] * other.m[1][1] + m[2][0] * other.m[1][2] + m[3][0] * other.m[1][3];
			//result.m[2][0] = m[0][0] * other.m[2][0] + m[1][0] * other.m[2][1] + m[2][0] * other.m[2][2] + m[3][0] * other.m[2][3];
			//result.m[3][0] = m[0][0] * other.m[3][0] + m[1][0] * other.m[3][1] + m[2][0] * other.m[3][2] + m[3][0] * other.m[3][3];

			////Second row
			//result.m[0][1] = m[0][1] * other.m[0][0] + m[1][1] * other.m[0][1] + m[2][1] * other.m[0][2] + m[3][1] * other.m[0][3];
			//result.m[1][1] = m[0][1] * other.m[1][0] + m[1][1] * other.m[1][1] + m[2][1] * other.m[1][2] + m[3][1] * other.m[1][3];
			//result.m[2][1] = m[0][1] * other.m[2][0] + m[1][1] * other.m[2][1] + m[2][1] * other.m[2][2] + m[3][1] * other.m[2][3];
			//result.m[3][1] = m[0][1] * other.m[3][0] + m[1][1] * other.m[3][1] + m[2][1] * other.m[3][2] + m[3][1] * other.m[3][3];

			////Third row
			//result.m[0][2] = m[0][2] * other.m[0][0] + m[1][2] * other.m[0][1] + m[2][2] * other.m[0][2] + m[3][2] * other.m[0][3];
			//result.m[1][2] = m[0][2] * other.m[1][0] + m[1][2] * other.m[1][1] + m[2][2] * other.m[1][2] + m[3][2] * other.m[1][3];
			//result.m[2][2] = m[0][2] * other.m[2][0] + m[1][2] * other.m[2][1] + m[2][2] * other.m[2][2] + m[3][2] * other.m[2][3];
			//result.m[3][2] = m[0][2] * other.m[3][0] + m[1][2] * other.m[3][1] + m[2][2] * other.m[3][2] + m[3][2] * other.m[3][3];

			////Fourth row
			//result.m[0][3] = m[0][3] * other.m[0][0] + m[1][3] * other.m[0][1] + m[2][3] * other.m[0][2] + m[3][3] * other.m[0][3];
			//result.m[1][3] = m[0][3] * other.m[1][0] + m[1][3] * other.m[1][1] + m[2][3] * other.m[1][2] + m[3][3] * other.m[1][3];
			//result.m[2][3] = m[0][3] * other.m[2][0] + m[1][3] * other.m[2][1] + m[2][3] * other.m[2][2] + m[3][3] * other.m[2][3];
			//result.m[3][3] = m[0][3] * other.m[3][0] + m[1][3] * other.m[3][1] + m[2][3] * other.m[3][2] + m[3][3] * other.m[3][3];

			return result;
		}

		Vector4 Math::Matrix4X4::operator*(const Vector3& other)
		{
			Vector4 result;

			result.x = m[0][0] * other.x + m[1][0] * other.y + m[2][0] * other.z + m[3][0] * 1.0f;
			result.y = m[0][1] * other.x + m[1][1] * other.y + m[2][1] * other.z + m[3][1] * 1.0f;
			result.z = m[0][2] * other.x + m[1][2] * other.y + m[2][2] * other.z + m[3][2] * 1.0f;
			result.w = m[0][3] * other.x + m[1][3] * other.y + m[2][3] * other.z + m[3][3] * 1.0f;

			return result;
		}

		Vector4 Matrix4X4::operator*(const Vector4& other)
		{
			Vector4 result;

			result.x = m[0][0] * other.x + m[1][0] * other.y + m[2][0] * other.z + m[3][0] * other.w;
			result.y = m[0][1] * other.x + m[1][1] * other.y + m[2][1] * other.z + m[3][1] * other.w;
			result.z = m[0][2] * other.x + m[1][2] * other.y + m[2][2] * other.z + m[3][2] * other.w;
			result.w = m[0][3] * other.x + m[1][3] * other.y + m[2][3] * other.z + m[3][3] * other.w;

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

		const Quaternion Math::Matrix4X4::ExtraxtRotation() const
		{
			return Quaternion(*this);
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
			Matrix4X4 rx = Matrix4X4();
			Matrix4X4 ry = Matrix4X4();
			Matrix4X4 rz = Matrix4X4();

			Vector3 rotationRadians;
			rotationRadians.x = rotation.x / 180.0f * M_PI;
			rotationRadians.y = rotation.y / 180.0f * M_PI;
			rotationRadians.z = rotation.z / 180.0f * M_PI;

			rz.m[0][0] = (float)cos(rotationRadians.z);  rz.m[0][1] = (float)sin(rotationRadians.z);	rz.m[0][2] = 0;	rz.m[0][3] = 0;
			rz.m[1][0] = -(float)sin(rotationRadians.z); rz.m[1][1] = (float)cos(rotationRadians.z);	rz.m[1][2] = 0;	rz.m[1][3] = 0;
			rz.m[2][0] = 0;								 rz.m[2][1] = 0;								rz.m[2][2] = 1;	rz.m[2][3] = 0;
			rz.m[3][0] = 0;								 rz.m[3][1] = 0;								rz.m[3][2] = 0;	rz.m[3][3] = 1;

			rx.m[0][0] = 1; rx.m[0][1] = 0;								 rx.m[0][2] = 0;								rx.m[0][3] = 0;
			rx.m[1][0] = 0; rx.m[1][1] = (float)cos(rotationRadians.x);  rx.m[1][2] = (float)sin(rotationRadians.x);	rx.m[1][3] = 0;
			rx.m[2][0] = 0; rx.m[2][1] = -(float)sin(rotationRadians.x); rx.m[2][2] = (float)cos(rotationRadians.x);	rx.m[2][3] = 0;
			rx.m[3][0] = 0; rx.m[3][1] = 0;								 rx.m[3][2] = 0;								rx.m[3][3] = 1;

			ry.m[0][0] = (float)cos(rotationRadians.y); ry.m[0][1] = 0; ry.m[0][2] = -(float)sin(rotationRadians.y);	ry.m[0][3] = 0;
			ry.m[1][0] = 0;								ry.m[1][1] = 1; ry.m[1][2] = 0;									ry.m[1][3] = 0;
			ry.m[2][0] = (float)sin(rotationRadians.y); ry.m[2][1] = 0; ry.m[2][2] = (float)cos(rotationRadians.y);		ry.m[2][3] = 0;
			ry.m[3][0] = 0;								ry.m[3][1] = 0; ry.m[3][2] = 0;									ry.m[3][3] = 1;

			return rz * ry * rx;

			//return CreateRotationMatrix(Quaternion::Euler(rotation));
		}

		Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Quaternion& rotation)
		{
			return CreateRotationMatrix(rotation.GetForward(), rotation.GetUp(), rotation.GetRight());
		}

		Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Vector3& forward, const Vector3& up)
		{
			Vector3 f = forward.Normalized();
			Vector3 u = up.Normalized();
			Vector3 r = Cross(u, f);

			return CreateRotationMatrix(f, u, r);
		}

		Matrix4X4 Math::Matrix4X4::CreateRotationMatrix(const Vector3& forward, const Vector3& up, const Vector3& right)
		{
			Matrix4X4 rotation = CreateIdentityMatrix();
			rotation.m[0][0] = right.x;		rotation.m[0][1] = right.y;		rotation.m[0][2] = right.z;		rotation.m[0][3] = 0;
			rotation.m[1][0] = up.x;		rotation.m[1][1] = up.y;		rotation.m[1][2] = up.z;		rotation.m[1][3] = 0;
			rotation.m[2][0] = forward.x;	rotation.m[2][1] = forward.y;	rotation.m[2][2] = forward.z;	rotation.m[2][3] = 0;
			rotation.m[3][0] = 0;			rotation.m[3][1] = 0;			rotation.m[3][2] = 0;			rotation.m[3][3] = 1;
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

			Matrix4X4 matScaleRotTrans = matScale * matRot * matTrans;

			return matScaleRotTrans;
		}

		Matrix4X4 Math::Matrix4X4::CreateScaleRotationTranslationMatrix(const Vector3& translation, const Quaternion& rotation, const Vector3& scale)
		{
			Matrix4X4 matTrans = Matrix4X4::CreateTranslationMatrix(translation);
			Matrix4X4 matRot = Matrix4X4::CreateRotationMatrix(rotation);
			Matrix4X4 matScale = Matrix4X4::CreateScalingMatrix(scale);

			Matrix4X4 matScaleRotTrans = matScale * matRot * matTrans;

			return matScaleRotTrans;
		}

		Matrix4X4 Math::Matrix4X4::CreateOrthographicProjectionMatrix(float left, float right, float bottom, float top, float nearPlane, float farPlane)
		{
			float rl = right - left;
			float tb = top - bottom;
			float fn = farPlane - nearPlane;

			Matrix4X4 ortho = Matrix4X4();

			//m[0] = 2.0f / rl;
			//m[5] = 2.0f / tb;
			//m[10] = -2.0f / fn;
			//m[12] = -(left + right) / rl;
			//m[13] = -(top + bottom) / tb;
			//m[14] = -(far + near) / fn;
			//m[15] = 1.0f;

			return Matrix4X4(
				2.0f / rl, 0, 0, 0,
				0, 2.0f / tb, 0, 0,
				0, 0, -2.0f / fn, -1,
				-(left + right) / rl, -(top + bottom) / tb, -(farPlane + nearPlane) / fn, 1.0f);

			/*ortho.m[0][0] = 2.0f / rl;	ortho.m[0][1] = 0;			ortho.m[0][2] = 0;			ortho.m[0][3] = -(right + left) / width;
			ortho.m[1][0] = 0;			ortho.m[1][1] = 2.0f / tb;	ortho.m[1][2] = 0;			ortho.m[1][3] = -(top + bottom) / height;
			ortho.m[2][0] = 0;			ortho.m[2][1] = 0;			ortho.m[2][2] = -2 / depth; ortho.m[2][3] = -(farPlane + nearPlane) / depth;
			ortho.m[3][0] = 0;			ortho.m[3][1] = 0;			ortho.m[3][2] = 0;			ortho.m[3][3] = 1;*/
			//return ortho;
		}

		Matrix4X4 Math::Matrix4X4::CreatePerspectiveProjectionMatrix(float fov, float width, float height, float zNear, float zFar)
		{
			float aspect = width / height;
			float tanHalfFovy = tan(fov / 2.0f);

			Matrix4X4 result;
			result.m[0][0] = 1.0f / (aspect * tanHalfFovy);
			result.m[1][1] = 1.0f / (tanHalfFovy);
			result.m[2][2] = -(zFar + zNear) / (zFar - zNear);
			result.m[2][3] = -1.0f;
			result.m[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
			return result;

			/*return Matrix4X4(
				xScale, 0, 0, 0,
				0, yScale, 0, 0,
				0, 0, (zFar + zNear) / nearmfar, -1,
				0, 0, 2 * zFar * zNear / nearmfar, 0);*/

			/*float aspectRatio = width / height;
			float tanHalfFOV = (float)tan(fov * M_PI / 180.0f / 2.0f);
			float zRange = zNear - zFar;

			Matrix4X4 perspective;
			perspective.m[0][0] = 1.0f / (tanHalfFOV * aspectRatio);	perspective.m[0][1] = 0.0f;					perspective.m[0][2] = 0.0f;						perspective.m[0][3] = 0.0f;
			perspective.m[1][0] = 0;									perspective.m[1][1] = 1.0f / tanHalfFOV;	perspective.m[1][2] = 0.0f;						perspective.m[1][3] = 0.0f;
			perspective.m[2][0] = 0;									perspective.m[2][1] = 0.0f;					perspective.m[2][2] = (-zNear - zFar) / zRange; perspective.m[2][3] = 2.0f * zFar * zNear / zRange;
			perspective.m[3][0] = 0;									perspective.m[3][1] = 0.0f;					perspective.m[3][2] = 1.0f;						perspective.m[3][3] = 0.0f;
			return perspective;*/
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
			//rot = rot.Conjugate();
			scale.x = 1.0f / scale.x;
			scale.y = 1.0f / scale.y;
			scale.z = 1.0f / scale.z;

			auto transMat = Matrix4X4::CreateTranslationMatrix(trans);
			auto rotMat = Matrix4X4::CreateRotationMatrix(rot);
			auto scaleMat = Matrix4X4::CreateScalingMatrix(scale);

			// Multiply matrices in oposite order
			auto scaleRotTransMat = transMat * rotMat * scaleMat;
			return scaleRotTransMat;
		}

		Vector4 Math::Matrix4X4::Row(int rowIndex) const
		{
			return Vector4(m[rowIndex][0], m[rowIndex][1], m[rowIndex][2], m[rowIndex][3]);
		}

		Vector4 Math::Matrix4X4::Col(int colIndex) const
		{
			return Vector4(m[0][colIndex], m[1][colIndex], m[2][colIndex], m[3][colIndex]);
		}

		Math::Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

		Math::Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

		Math::Quaternion::Quaternion(const Matrix4X4& rotation)
		{
			float trace = rotation.m[0][0] + rotation.m[1][1] + rotation.m[2][2];

			if (trace > 0)
			{
				float s = 0.5f / (float)sqrt(trace + 1.0f);
				w = 0.25f / s;
				x = (rotation.m[2][1] - rotation.m[1][2]) * s;
				y = (rotation.m[0][2] - rotation.m[2][0]) * s;
				z = (rotation.m[1][0] - rotation.m[0][1]) * s;
			}
			else
			{
				if (rotation.m[0][0] > rotation.m[1][1] && rotation.m[0][0] > rotation.m[2][2])
				{
					float s = 2.0f * (float)sqrt(1.0f + rotation.m[0][0] - rotation.m[1][1] - rotation.m[2][2]);
					w = (rotation.m[2][1] - rotation.m[1][2]) / s;
					x = 0.25f * s;
					y = (rotation.m[0][1] + rotation.m[1][0]) / s;
					z = (rotation.m[0][2] + rotation.m[2][0]) / s;
				}
				else if (rotation.m[1][1] > rotation.m[2][2])
				{
					float s = 2.0f * (float)sqrt(1.0f + rotation.m[1][1] - rotation.m[0][0] - rotation.m[2][2]);
					w = (rotation.m[0][2] - rotation.m[2][0]) / s;
					x = (rotation.m[0][1] + rotation.m[1][0]) / s;
					y = 0.25f * s;
					z = (rotation.m[1][2] + rotation.m[2][1]) / s;
				}
				else
				{
					float s = 2.0f * sqrt(1.0f + rotation.m[2][2] - rotation.m[0][0] - rotation.m[1][1]);
					w = (rotation.m[1][0] - rotation.m[0][1]) / s;
					x = (rotation.m[0][2] + rotation.m[2][0]) / s;
					y = (rotation.m[2][1] + rotation.m[1][2]) / s;
					z = 0.25f * s;
				}
			}

			float length = (float)sqrt(x * x + y * y + z * z + w * w);
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}

		Quaternion::Quaternion(Vector3 axis, float angle)
		{
			float sinHalfAngle = sin(angle / 2.0f);
			float cosHalfAngle = cos(angle / 2.0f);

			x = axis.x * sinHalfAngle;
			y = axis.y * sinHalfAngle;
			z = axis.z * sinHalfAngle;
			w = cosHalfAngle;
		}

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

		Quaternion Quaternion::Lerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
		{
			float num = amount;
			float num2 = 1.0f - num;
			Quaternion quaternion = Quaternion();
			float num5 = (((quaternion1.x * quaternion2.x) + (quaternion1.y * quaternion2.y)) + (quaternion1.z * quaternion2.z)) + (quaternion1.w * quaternion2.w);
			if (num5 >= 0.0f)
			{
				quaternion.x = (num2 * quaternion1.x) + (num * quaternion2.x);
				quaternion.y = (num2 * quaternion1.y) + (num * quaternion2.y);
				quaternion.z = (num2 * quaternion1.z) + (num * quaternion2.z);
				quaternion.w = (num2 * quaternion1.w) + (num * quaternion2.w);
			}
			else
			{
				quaternion.x = (num2 * quaternion1.x) - (num * quaternion2.x);
				quaternion.y = (num2 * quaternion1.y) - (num * quaternion2.y);
				quaternion.z = (num2 * quaternion1.z) - (num * quaternion2.z);
				quaternion.w = (num2 * quaternion1.w) - (num * quaternion2.w);
			}
			float num4 = (((quaternion.x * quaternion.x) + (quaternion.y * quaternion.y)) + (quaternion.z * quaternion.z)) + (quaternion.w * quaternion.w);
			float num3 = 1.0f / sqrt(num4);
			quaternion.x *= num3;
			quaternion.y *= num3;
			quaternion.z *= num3;
			quaternion.w *= num3;
			return quaternion;
		}

		Quaternion Quaternion::Slerp(Quaternion quaternion1, Quaternion quaternion2, float amount)
		{
			float num2;
			float num3;
			Quaternion quaternion;
			float num = amount;
			float num4 = (((quaternion1.x * quaternion2.x) + (quaternion1.y * quaternion2.y)) + (quaternion1.z * quaternion2.z)) + (quaternion1.w * quaternion2.w);
			bool flag = false;
			if (num4 < 0.0f)
			{
				flag = true;
				num4 = -num4;
			}
			if (num4 > 0.999999f)
			{
				num3 = 1.0f - num;
				num2 = flag ? -num : num;
			}
			else
			{
				float num5 = acos(num4);
				float num6 = (1.0 / sin(num5));
				num3 = (sin((1.0f - num) * num5)) * num6;
				num2 = flag ? (sin(num * num5)) * num6 : ((sin(num * num5)) * num6);
			}
			quaternion.x = (num3 * quaternion1.x) + (num2 * quaternion2.x);
			quaternion.y = (num3 * quaternion1.y) + (num2 * quaternion2.y);
			quaternion.z = (num3 * quaternion1.z) + (num2 * quaternion2.z);
			quaternion.w = (num3 * quaternion1.w) + (num2 * quaternion2.w);
			return quaternion;
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

		Vector4 Math::Vector4::operator*(const Vector4& other) const
		{
			Vector4 result;
			result.x = x * other.x;
			result.y = y * other.y;
			result.z = z * other.z;
			result.w = w * other.w;
			return result;
		}

		Vector4 Vector4::operator*(float factor) const
		{
			Vector4 result;
			result.x = x * factor;
			result.y = y * factor;
			result.z = z * factor;
			result.w = w * factor;
			return result;
		}

		Vector4 Math::Vector4::operator/(float factor) const
		{
			Vector4 result;
			result.x = x / factor;
			result.y = y / factor;
			result.z = z / factor;
			result.w = w / factor;
			return result;
		}

		Vector4 Math::CalculateOffsets(const Origin& allignment, const Vector2& dimensions)
		{
			Vector2 halfDimensions = dimensions;
			halfDimensions = halfDimensions / 2.0f;

			switch (allignment)
			{
			case Math::BottomLeft:
				return Vector4(0.0f, 0.0f, dimensions.x, dimensions.y);
			case Math::TopLeft:
				return Vector4(0.0f, -dimensions.y, dimensions.x, 0.0f);
			case Math::BottomRight:
				return Vector4(-dimensions.x, 0.0f, 0.0f, dimensions.y);
			case Math::TopRight:
				return Vector4(-dimensions.x, -dimensions.y, 0.0f, 0.0f);

			case Math::Center:
				return Vector4(-halfDimensions.x, -halfDimensions.y, halfDimensions.x, halfDimensions.y);

			case Math::RightCenter:
				return Vector4(-dimensions.x, -halfDimensions.y, 0.0f, halfDimensions.y);
			case Math::LeftCenter:
				return Vector4(0.0f, -halfDimensions.y, dimensions.x, halfDimensions.y);
			case Math::TopMiddle:
				return Vector4(-halfDimensions.x, -dimensions.y, halfDimensions.x, 0.0f);
			case Math::BottomMiddle:
				return Vector4(-halfDimensions.x, 0.0f, halfDimensions.x, dimensions.y);
			}

			return Vector4();
		}

		Ray::Ray(Vector3 start, Vector3 direction)
		{
			Start = start;
			Direction = direction;
		}

		Vector3 Ray::GetPoint(float length)
		{
			return Start + Direction * length;
		}

		btVector3 TobtVector3(const Vector3& vec3)
		{
			return btVector3((btScalar)vec3.x, (btScalar)vec3.y, (btScalar)vec3.z);
		}

		Vector3 btToVector3(const btVector3& vec3)
		{
			return Vector3((float)vec3.getX(), (float)vec3.getY(), (float)vec3.getZ());
		}

		btQuaternion TobtQuaternion(const Quaternion& quaternion)
		{
			return btQuaternion((btScalar)quaternion.x, (btScalar)quaternion.y, (btScalar)quaternion.z, (btScalar)quaternion.w);
		}

		Quaternion btToQuaternion(const btQuaternion& quaternion)
		{
			return Quaternion((float)quaternion.getX(), (float)quaternion.getY(), (float)quaternion.getZ(), (float)quaternion.getW());
		}
	}
}