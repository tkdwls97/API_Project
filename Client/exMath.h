#pragma once
#include <cmath>

namespace ex::math
{
#define PI 3.141592f

	struct Vector2
	{
		Vector2();
		Vector2(float _x, float _y);
		Vector2(float _value);

		// ��Ģ���� ������ ������
		// float���� ���� ��� Vector2�� x,y ���п� ���޹��� ���� ��Ģ�����Ͽ� ��ȯ�Ѵ�.
		Vector2 operator/(const float _value);
		Vector2 operator*(const float _value);
		Vector2 operator+(const float _value);
		Vector2 operator-(const float _value);
		
		void operator/=(const float _value);
		void operator+=(const float _value);
		void operator-=(const float _value);

		// Vector2�� ���� ��� ���޹��� Vector2�� ������ ������
		// �� ������ ���п� ��Ģ�����Ͽ� ��ȯ�Ѵ�.
		Vector2 operator/(const Vector2& _value);
		Vector2 operator*(const Vector2& _value);
		Vector2 operator+(const Vector2& _value);
		Vector2 operator-(const Vector2& _value);

		void operator/=(const Vector2& _value);
		void operator*=(const Vector2& _value);
		void operator-=(const Vector2& _value);
		Vector2& operator*=(const float& _value);
		Vector2& operator+=(const Vector2& _other);
		

		bool operator ==(const Vector2 _other);
		bool operator<=(const Vector2 _other);
		bool operator>=(const Vector2 _other);

		Vector2 operator-();

		void Clear();
		float Length();
		Vector2 Normalize();

		float x;
		float y;

		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

	};

	inline Vector2 Rotate(Vector2 _vector, float _degree)
	{
		float radian = (_degree / 180.f) * PI;
		_vector.Normalize();
		float x = cosf(radian) * _vector.x - sinf(radian) * _vector.y;
		float y = sinf(radian) * _vector.x + cosf(radian) * _vector.y;

		return Vector2(x, y);
	}

	inline float Dot(Vector2& _v1, Vector2& _v2)
	{
		return _v1.x * _v2.x + _v1.y * _v2.y;
	}

	inline float Cross(Vector2 _v1, Vector2 _v2)
	{
		return _v1.x * _v2.y - _v1.y * _v2.x;
	}
}


