#pragma once
#include "exScene.h"

namespace ex
{
	class StageScene2 : public Scene
	{
	public:
		StageScene2();
		virtual ~StageScene2();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
	};
}
