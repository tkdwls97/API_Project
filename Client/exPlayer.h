#pragma once
#include "exGameObject.h"


namespace ex
{
	class GameEffect;
	class Transform;
	class Animator;
	class Collider;
	class Rigidbody;
	class Texture;

	class Player : public GameObject
	{
	private:
		struct PlayerInfo
		{
			int mHp;
			int mMP;
			int mSpeed;
			int mDamage;
			int mDef;
			int mLevel;

		};

	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		eState GetState() { return mState; }
		void SetState(eState _state) { mState = _state; }

		bool IsPotalState() { return mbPortalState; }
		void SetPotalState(bool _state) { mbPortalState = _state; }

		bool IsRopeState() { return mbRopeState ; }
		void SetRopeState(bool _state) { mbRopeState = _state; }


		void Idle();
		void Move();
		void Down();
		void Rope();
		//void RopeDown();
		void Attack();
		void Skill();
		void Fall();
		void Jump();
		//void DoubleJump();
		void Hit();
		void Death();

	private:
		Animator*		mAnimator;
		Transform*		mTransform;
		Rigidbody*		mRigidbody;
		Collider*		mCollider;
		eState			mState;
		PlayerInfo		mInfo;

		bool			mbPortalState;
		bool			mbRopeState;
		bool			mbInvincible;
		float			mhitDelay;
	};
}
