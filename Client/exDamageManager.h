#pragma once
#include "exUI.h"
#include "exTexture.h"

namespace ex
{
	class Transform;

	class DamageManager : public UI
	{
	public:
		DamageManager();
		virtual ~DamageManager();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void PlayDamageAnimation(int _skillDamage);

		Texture* GetDamageArr() { return *mDamageArr; }
		int GetPlayerDamage() { return mPlayerDamage; }

		int GetDamageSize() { return mDamageSize; }

		int GetDamageIndex() { return mDamageIndex; }


	private:
		Texture* mDamageArr[10];
		int		 mDamageIndexArr[10];
		int		 mPlayerDamage;
		int		 mDamageSize;
		int		 mDamageIndex;
	};

}
