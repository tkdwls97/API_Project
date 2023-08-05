#pragma once
#include "exGameObject.h"

namespace ex
{

	class EffectManger : public GameObject
	{
	public:
		EffectManger(GameObject* _owner);
		virtual ~EffectManger();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;


	};

}
