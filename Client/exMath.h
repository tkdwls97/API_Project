#pragma once
#include <cmath>

namespace ex::math
{
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
		void operator*=(const float _value);
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
		void operator+=(const Vector2& _value);
		void operator-=(const Vector2& _value);

		bool operator ==(const Vector2 _other);

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

	

}