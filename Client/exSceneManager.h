#pragma once
#include "exScene.h"


namespace ex
{
	class Player;
	class PlayerAttack;
	class StatusBar;
	class ExpBar;
	class HpBar;
	class MpBar;

	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);

		template <typename T>
		static T* CreateScene(const std::wstring& _name)
		{
			T* scene = new T();
			scene->SetName(_name);
			mScenes.insert(std::make_pair(_name, scene));
			mActiveScene = scene;
			scene->Initialize();

			return scene;
		}

		static Scene* LoadScene(const std::wstring& _name);
		static Scene* GetActiveScene() { return mActiveScene; }


		static Player* GetPlayer() { return mPlayer; }
		static PlayerAttack* GetPlayerAttack() { return mPlayerAtt; }
		static StatusBar* GetStatusBar() { return mStatusBar; }
						
	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static Player* mPlayer;
		static PlayerAttack* mPlayerAtt;
		static StatusBar*	mStatusBar;
		static ExpBar* mExpBar;
		static HpBar* mHpBar;
		static MpBar* mMpBar;
	};

}
