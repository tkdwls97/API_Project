#pragma once
#include "exScene.h"

namespace ex
{
	class BossScene : public Scene
	{
	public:
		BossScene();
		virtual ~BossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:

	};
}
