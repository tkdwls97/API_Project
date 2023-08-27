#pragma once
#include "exScene.h"

namespace ex
{
	class Sound;

	class BossScene2 : public Scene
	{
	public:
		BossScene2();
		virtual ~BossScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Sound* mBossScene2_Sound;
	};
}
