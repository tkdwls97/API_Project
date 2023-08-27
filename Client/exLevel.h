#pragma once
#include "exUI.h"

namespace ex
{
	class Transform;
	class Texture;
	class Animator;

	class Level : public UI
	{
	public:
		Level();
		virtual ~Level();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void PlayLevelAnimation(int _level);

	private:
		Texture* mLevelArr[10];
	};

}
