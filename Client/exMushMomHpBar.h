#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Collider;
	class Texture;
	class MushMom;

	class MushMomHpBar : public UI
	{
	public:
		MushMomHpBar(MushMom* _owner);
		virtual ~MushMomHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		Texture* mMushMomHpBar;
		MushMom* mMushMom;
		int		 mMushMomHp;
		int		 mMushMomMaxHp;
		float	 mReductionHp;

	};

}
