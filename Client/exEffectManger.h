#pragma once
#include "exGameObject.h"

namespace ex
{
	class Collider;
	class Transform;
	class Animator;

	class EffectManger : public GameObject
	{
	public:
		struct EffectInfo
		{
			int AttackCount;
			int DamagePercentage;
		};

	public:
		EffectManger(GameObject* _owner);
		virtual ~EffectManger();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		EffectInfo GetEffectInfo() { return mEffectInfo; }
		void SetEffectInfo(EffectInfo _info) {  mEffectInfo = _info; }

		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
		EffectInfo  mEffectInfo;
	};

}
