#pragma once
#include "exScene.h"

namespace ex
{
	class Login;
	class Sound;
	class Animator;
	class Transform;
	class GameObject;

	class OpeningScene : public Scene
	{
	public:
		OpeningScene();
		virtual ~OpeningScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void SceneIN() override;
		virtual void SceneOut() override;

		void SoundLoad();
	private:
		GameObject* mVideo;
		Animator* mAnimator;
		Transform* mTransform;
		Sound* mOpeningSound;
	};
}
