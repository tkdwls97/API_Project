#pragma once
#include "exEffectManger.h"

namespace ex
{
	class Animator;
	class Collider;
	class Transform;
	class Animation;
	class Sound;

	class ComboDeathFaultHit : public EffectManger
	{
	public:
		ComboDeathFaultHit();
		virtual ~ComboDeathFaultHit();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void SetPos(math::Vector2 _pos) { mPos = _pos; }

	private:
		math::Vector2 mPos;
		Animator* mAnimator;
		Transform* mTransform;
		Sound* mComboDeathFaultHitSound;
	};

}
