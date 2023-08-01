#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Collider;
	class Transform;
	class Animator;

	class ObejctAttack : public EffectManger
	{
	public:
		ObejctAttack(GameObject* _owner);
		virtual ~ObejctAttack();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:
		GameObject* mOwner;
		
	};

}
