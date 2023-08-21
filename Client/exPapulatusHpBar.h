#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Collider;
	class Texture;
	class Papulatus;

	class PapulatusHpBar : public UI
	{
	public:
		PapulatusHpBar(Papulatus* _owner);
		virtual ~PapulatusHpBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		Texture* mPapulatusHpBar;
		Papulatus* mPapulatus;
		int		 mPapulatusHp;
		int		 mPapulatusMaxHp;
		float	 mReductionHp;

	};

}
