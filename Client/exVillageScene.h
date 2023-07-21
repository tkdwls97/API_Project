#pragma once
#include "exScene.h"


namespace ex
{
	class VillageScene: public Scene
	{
	public:
		VillageScene();
		virtual ~VillageScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	private:
	};
}

