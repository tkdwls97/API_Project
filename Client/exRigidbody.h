#pragma once
#include "exComponent.h"

namespace ex
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);


		void AddForce(math::Vector2 _force) { mForce += _force; }
		void SetMass(float _mass) { mMass = _mass; }

		void  SetFriction(float _friction) { mFriction = _friction; }
		float GetFriction() { return mFriction; }

		void SetGround(bool _ground) { mbGround = _ground; }
		bool GetGround() { return mbGround; }

		math::Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(math::Vector2 _velocity) { mVelocity = _velocity; }

		void SetVelocityY(float _velocity) { mVelocity.y = _velocity; }
		void SetVelocityX(float _velocity) { mVelocity.x = _velocity; }

		math::Vector2 GetGravity() { return mGravity; }
		void SetGravity(math::Vector2 _gravity) { mGravity = _gravity; }

		void SetLimitedVeloctyX(float _limited) { mLimitedVelocty.x = _limited; }
		float GetLimitedVeloctyX() { return mLimitedVelocty.x; }
		

	private:
		// ����
		float mMass;
		// ������
		float mFriction;
		//// ���� ������
		//float mStaticFriction;
		//// � ������
		//float mKineticFrction;
	
		// ���
		//float mCoefficentFrction;

		// ��
		math::Vector2 mForce;
		// ���ӵ�
		math::Vector2 mAccelation;
		// �ӵ�
		math::Vector2 mVelocity;
		// �߷� ���ӵ�
		math::Vector2 mGravity;

		// ���ӵ��� ���� �� �ִ� �ӵ��� �����ϴ� ����Ʈ ����
		math::Vector2 mLimitedVelocty;

		// true -> ���� ���� ���� false -> ���߿� �� ����
		bool mbGround;
	};

}
