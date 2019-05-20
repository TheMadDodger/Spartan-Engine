#pragma once

namespace Math
{
	struct Vector2
	{
		float x;
		float y;

		// Constructors
		Vector2() { x = 0; y = 0; }
		Vector2(float _x, float _y) { x = _x; y = _y; }

		// Math operations
		float Length();
		float Magnitude() { return Length(); }
		float Normalize();

		Vector2 operator+(const Vector2 &other);
		void operator+=(const Vector2 &other);
		Vector2 operator-(const Vector2 &other);
		Vector2 operator*(const Vector2 &other);
		Vector2 operator*(float factor);
		void operator*=(float factor);
		Vector2 operator/(float factor);
		Vector2 Normalized();

		// Static methods
		static Vector2 Zero() { return Vector2(); }
		static Vector2 Forward() { return Vector2(0, 1); }
		static Vector2 Back() { return Vector2(0, -1); }
		static Vector2 Right() { return Vector2(1, 0); }
		static Vector2 Left() { return Vector2(-1, 0); }
		static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);

		std::string ToString()
		{
			return std::string(std::to_string(x) + std::to_string(y));
		}
	};

	struct Vector3
	{
		float x;
		float y;
		float z;

		// Constructors
		Vector3() { x = 0; y = 0; z = 0; }
		Vector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }

		// Math operations
		float Length();
		float Magnitude() { return Length(); }
		float Normalize();

		Vector3 operator+(const Vector3 &other);
		Vector3 operator-(const Vector3 &other);
		Vector3 operator*(const Vector3 &other);
		Vector3 operator*(float factor);
		Vector3 operator/(float factor);
		Vector3 Normalized();

		// Static methods
		static Vector3 Zero() { return Vector3(); }
		static Vector3 Forward() { return Vector3(1, 0, 0); }
		static Vector3 Back() { return Vector3(-1, 0, 0); }
		static Vector3 Right() { return Vector3(0, 1, 0); }
		static Vector3 Left() { return Vector3(0, -1, 0); }
		static Vector3 Up() { return Vector3(0, 0, 1); }
		static Vector3 Down() { return Vector3(0, 0, -1); }
	};

	struct Float4
	{
		Float4() : x(0), y(0), w(0), h(0) {}
		Float4(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h) {}

		float x;
		float y;
		float w;
		float h;
	};

	struct Matrix3X3
	{
		Matrix3X3() : m{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} } {}

		float m[3][3];

		Matrix3X3(float m11, float m12, float m13,
				  float m21, float m22, float m23,
				  float m31, float m32, float m33)
		{
			m[0][0] = m11; m[1][0] = m12; m[2][0] = m13;
			
			m[0][1] = m21; m[1][1] = m22; m[2][1] = m23;
			
			m[0][2] = m31; m[1][2] = m32; m[2][2] = m33;
		}

		Matrix3X3 operator*(const Matrix3X3 &other);
		Vector3 operator*(const Vector3 &other);
		Matrix3X3 operator*(float factor);
		Matrix3X3 operator+(const Matrix3X3 &other);

		const Vector2 ExtraxtTranslation() const;
		const Vector3 ExtraxtRotation() const;
		const Vector2 ExtraxtScale() const;

		static Matrix3X3 CreateIdentityMatrix();
		static Matrix3X3 CreateTranslationMatrix(const Vector2 &translation);
		static Matrix3X3 CreateRotationMatrix(const Vector3 &rotation);
		static Matrix3X3 CreateScalingMatrix(const Vector2 &scale);
		static Matrix3X3 CreateScaleRotationTranslationMatrix(const Vector2 &translation, const Vector3 &rotation, const Vector2 &scale);

		Matrix3X3 Inverse() const;
	};

	struct Color
	{
	public: // Constructors
		Color() : r(0), g(0), b(0), a(0) {}
		Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {}

	public: // Static methods color library
		static Color Red() { return Color(1, 0, 0, 1); }
		static Color Green() { return Color(0, 1, 0, 1); }
		static Color Blue() { return Color(0, 0, 1, 1); }
		static Color Black() { return Color(0, 0, 0, 1); }
		static Color White() { return Color(1, 1, 1, 1); }
		static Color Magenta() { return Color(1, 0, 1, 1); }
		static Color Purple() { return Color(0.5f, 0, 0.5f, 1); }
		static Color Cyan() { return Color(0, 1, 1, 1); }
		static Color Yellow() { return Color(1, 1, 0, 1); }
		static Color Gold() { return Color(1, 0.84f, 0, 1); }
		static Color Pink() { return Color(1, 0.41f, 0.7f, 1); }
		static Color LightGray() { return Color(0.82f, 0.82f, 0.82f, 1); }
		static Color Gray() { return Color(0.5f, 0.5f, 0.5f, 1); }
		static Color DarkGray() { return Color(0.66f, 0.66f, 0.66f, 1); }
		static Color Silver() { return Color(0.75f, 0.75f, 0.75f, 1); }

		static Color Lerp(const Color &a, const Color &b, float t);

	public: // Operators
		void operator*=(float factor);
		Color operator*(float f);
		Color operator-(const Color &other);
		Color operator+(const Color &other);
		bool operator==(const Color &other);
		bool operator!=(const Color &other);

	public: // Color values
		float r;
		float g;
		float b;
		float a;
	};

	inline float Distance(Vector2 &pos1, Vector2 &pos2)
	{
		// Calculate Vector2 from end point to begin point
		auto p12 = pos2 - pos1;

		// Return the length of this Vector2
		return p12.Length();
	}

	inline Vector2 LengthDir(float length, float dir)
	{
		Vector2 result = Vector2::Zero();
		float radians = dir / 180.0f * M_PI;
		result.x = cos(radians) * length;
		result.y = sin(radians) * length;
		return result;
	}

	inline Vector2 LengthDirRad(float length, float dir)
	{
		Vector2 result = Vector2::Zero();
		result.x = cos(dir) * length;
		result.y = sin(dir) * length;
		return result;
	}

	template<typename T>
	inline T RandomRange(T a, T b)
	{
		/*if (typeid(T) == typeid(Color))
		{
			float diff = (Color)b - (Color)a;
			float randomFactor = (float)rand() / (float)RAND_MAX;
			return (randomFactor * diff) + (Color)a);
		}*/

		T diff = b - a;
		float randomFactor = (float)rand() / (float)RAND_MAX;
		return (T)((diff * randomFactor) + a);
	}

	template<typename T>
	inline T Random()
	{
		float randomFactor = (float)rand() / (float)RAND_MAX;
		return (T)randomFactor;
	}

	inline Vector2 RandomRangeVector2(const Vector2 &a, const Vector2 &b)
	{
		float x, y;
		x = RandomRange<float>(a.x, b.x);
		y = RandomRange<float>(a.y, b.y);

		return Vector2(x, y);
	}

	template<typename T>
	inline int Absolute(T &value)
	{
		int sine = (int)(value / abs(value));
		value = abs(value);
		return sine;
	}

	inline float Lerp(float a, float b, float t)
	{
		return (1 - t) * a + t * b;
	}

	enum Origin
	{
		TopLeft,
		TopMiddle,
		TopRight,

		LeftCenter,
		Center,
		RightCenter,

		BottomLeft,
		BottomMiddle,
		BottomRight,
	};

	struct Rect
	{
		Rect(Vector2 topLeft, Vector2 bottomRight) : TopLeft(topLeft), BottomRight(bottomRight) {}

		Vector2 TopLeft;
		Vector2 BottomRight;
	};

	inline bool CheckPointInRect(const Vector2 &point, const Rect &rect)
	{
		if (point.x >= rect.TopLeft.x)
			if (point.y >= rect.TopLeft.y)
				if (point.x <= rect.BottomRight.x)
					if (point.y <= rect.BottomRight.y)
						return true;

		return false;
	}

	inline Matrix3X3 BlendMatrices(Matrix3X3 &m1, float blend1, Matrix3X3 &m2, float blend2)
	{
		return m1 * blend1 + m2 * blend2;
	}

	inline float Dot(const Vector2 &v1, const Vector2 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline float Dot(const Vector3 &v1, const Vector3 &v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline Vector3 Cross(const Vector2 &a, const Vector2 &b)
	{
		Vector3 crossProduct = Vector3::Zero();
		crossProduct.x = 0.0f;
		crossProduct.y = 0.0f;
		crossProduct.z = a.x * b.y - a.y * b.x;
		return crossProduct;
	}

	inline Vector3 Cross(const Vector3 &a, const Vector3 &b)
	{
		Vector3 crossProduct = Vector3::Zero();
		crossProduct.x = a.y * b.z - a.z * b.y;
		crossProduct.y = a.z * b.x - a.x - b.z;
		crossProduct.z = a.x * b.y - a.y * b.x;
		return crossProduct;
	}

	inline b2Vec2 Vector2ToBox2DVec2(const Vector2 &vec)
	{
		return b2Vec2(vec.x, vec.y);
	}

	template<typename T>
	inline T Clamp(T min, T max, T value)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}
