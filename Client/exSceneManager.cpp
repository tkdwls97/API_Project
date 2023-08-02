#include "exSceneManager.h"
#include "exTitleScene.h"
#include "exStageScene.h"
#include "exInput.h"
#include "exBossScene.h"
#include "exStageScene2.h"
#include "exVillageScene.h"
#include "exPlayer.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<StageScene2>(L"StageScene2");
		CreateScene<BossScene>(L"BossScene");
		CreateScene<VillageScene>(L"VillageScene");

		for (auto iter : mScenes)
		{
			mActiveScene = iter.second;
			iter.second->Initialize();
		}

		mPlayer->Initialize();
		LoadScene(L"TitleScene");
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::Render(HDC _hdc)
	{
		mActiveScene->Render(_hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& _name)
	{
		mActiveScene->SceneOut();

		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(_name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene = iter->second;

		// Å¸ÀÌÆ² ¾À End¾ÀÀÌ ¾Æ´Ï¸é ÇÃ·¹ÀÌ¾î¸¦ ¾À¿¡ ³Ö¾îÁÜ
		if (_name != L"TitleScene" && _name != L"EndScene")
		{
			mActiveScene->AddGameObject(enums::eLayerType::Player, mPlayer);
		}
		mActiveScene->SceneIN();

		return iter->second;
	}

}