#pragma once
#include "exScene.h"


namespace ex
{
	class Portal;
	class MushMomScene : public Scene
	{
	public:
		MushMomScene();
		virtual ~MushMomScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

	private:
		Portal* mPortal;
	};
}

