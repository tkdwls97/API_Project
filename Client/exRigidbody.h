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
		// ����
		float mMass;
		// ������
		float mFriction;
		//// ���� ������
		//float mStaticFriction;
		//// � ������
		//float mKineticFrction;
		// ���
		float mCoefficentFrction;

		// ��
		math::Vector2 mForce;
		// ���ӵ�
		math::Vector2 mAccelation;
		// �ӵ�
		math::Vector2 mVelocity;
		//�ִ� �ӵ�
		math::Vector2 mMaxVelocity;
		// �߷� ���ӵ�
		math::Vector2 mGravity;
	};

}
