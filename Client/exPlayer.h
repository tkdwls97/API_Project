#pragma once
#include "exGameObject.h"



namespace ex
{
	class GameEffect;
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;

	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		eState GetState() { return mState; }

		void Idle();
		void Move();
		void Down();
		void Rope();
		void Attack();
		void Skill();
		void Fall();
		void Jump();
		void Death();

	private:
		Animator*	mAnimator;
		Transform*  mTransform;
		Rigidbody*  mRigidbody;
		Collider*   mCollider;
		eState		mState;


	};
}
