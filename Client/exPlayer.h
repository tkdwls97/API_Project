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

		void Idle();
		void Move();
		void Down();
		void Rope();
		void Attack();
		void Skill();
		void Jump();
		void Death();
		void DownJump();

	private:
		Animator*	mAnimator;
		eState		mState;
		Rigidbody*  mRigidbody;


	};
}
