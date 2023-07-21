#pragma once
#include "exGameObject.h"

namespace ex
{
	class Animator;

	class GameEffect : public GameObject
	{
	public:
		GameEffect();
		virtual ~GameEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		void PlayEffect(enums::eMoveDir _dir);

	private:
		Animator* mAnimator;
	};

}
