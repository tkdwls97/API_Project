#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Collider;
	class Texture;
	class Monsters;

	class MonstersBar : public UI
	{
	public:
		MonstersBar(Monsters* _owner);
		virtual ~MonstersBar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

	private:
		Texture* mMonstersHpBar;
		Texture* mMonsterEmptyHpBar;
		Monsters* mMonsters;

		int		 mMonstersHp;
		int		 mMonstersMaxHp;
		float	 mReductionHp;

	};

}
