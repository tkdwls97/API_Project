#pragma once
#include "exUI.h"
#include "exTexture.h"

namespace ex
{
	class Transform;

	class DamageSkin : public UI
	{
	public:
		DamageSkin();
		virtual ~DamageSkin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		Texture* GetDamageArr() { return *mDamageArr; }
		int GetPlayerDamage() { return mPlayerDamage; }

	private:
		Texture* mDamageArr[10];
		int		 mPlayerDamage;
	};

}
