#pragma once
#include "exScene.h"


namespace ex
{
	class Player;
	class StatusBar;
	class ExpBar;
	class HpBar;
	class MpBar;
	class DamageManager;
	class MushMomHpBar;

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
		static StatusBar* GetStatusBar() { return mStatusBar; }
		static DamageManager* GetDamageManager() { return mDamageManager; }

		static bool GetPortalCheck() { return mbPortalCheck; }
		static void SetPortalCheck(bool _data) { mbPortalCheck = _data; }
	private:
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;
		static Player* mPlayer;
		static StatusBar* mStatusBar;
		static ExpBar* mExpBar;
		static HpBar* mHpBar;
		static MpBar* mMpBar;
		static DamageManager* mDamageManager;
		static bool mbPortalCheck;
	};

}
