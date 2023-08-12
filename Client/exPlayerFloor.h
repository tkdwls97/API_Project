#pragma once
#include "exPlayer.h"


namespace ex
{
	class Transform;
	class Rigidbody;
	class Collider;
	class Texture;

	class PlayerFloor : public Player
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
		PlayerFloor(GameObject* _owner);
		virtual ~PlayerFloor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		Transform* GetTransform() { return mTransform; }
		Collider* GetCollider() { return mCollider; }
		Rigidbody* GetRigidbody() { return mRigidbody; }

	private:
		Transform* mTransform;
		Collider* mCollider;
		Rigidbody* mRigidbody;
		GameObject* mOwner;
	};
}
