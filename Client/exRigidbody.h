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

	private:
		// 무게
		float mMass;
		// 마찰력
		float mFriction;
		//// 정지 마찰력
		//float mStaticFriction;
		//// 운동 마찰력
		//float mKineticFrction;
		// 계수
		float mCoefficentFrction;

		// 힘
		math::Vector2 mForce;
		// 가속도
		math::Vector2 mAccelation;
		// 속도
		math::Vector2 mVelocity;
		//최대 속도
		math::Vector2 mMaxVelocity;
		// 중력 가속도
		math::Vector2 mGravity;
	};

}
