#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Collider;
	class Transform;
	class Animator;

	class PlayerAttack : public EffectManger
	{
	public:
		PlayerAttack(GameObject* _owner);
		virtual ~PlayerAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		GameObject* mOwner;
	};

}