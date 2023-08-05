#pragma once
#include "exMonsters.h"

namespace ex
{
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;
	class Texture;

	class GreenMush : public Monsters
	{
	public:
		GreenMush();
		virtual ~GreenMush();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void Idle();
		void Move();
		void Attack();
		void Chase();
		void Hit();
		void Dead();

	private:
		Animator*		mAnimator;
		Transform*		mTransform;
		Rigidbody*		mRigidbody;
		Collider*		mCollider;
		eMonsterState	mMonsterState;
	};

}
