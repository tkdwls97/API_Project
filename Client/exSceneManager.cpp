#include "exSceneManager.h"
#include "exTitleScene.h"
#include "exStageScene.h"
#include "exInput.h"
#include "exBossScene.h"
#include "exStageScene2.h"
#include "exVillageScene.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exPlayerAttack.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;
	PlayerAttack* SceneManager::mPlayerLeftAtt = new PlayerAttack(mPlayer);
	PlayerAttack* SceneManager::mPlayerRightAtt = new PlayerAttack(mPlayer);
	
	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<VillageScene>(L"VillageScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<StageScene2>(L"StageScene2");
		CreateScene<BossScene>(L"BossScene");

		for (auto iter : mScenes)
		{
			mActiveScene = iter.second;
			iter.second->Initialize();
		}

		mPlayer->Initialize();
		mPlayer->GetComponent<Transform>()->SetMoveDir(enums::eMoveDir::Left);
		mPlayerLeftAtt->Initialize();
		mPlayer->GetComponent<Transform>()->SetMoveDir(enums::eMoveDir::Right);
		mPlayerRightAtt->Initialize();



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
			mActiveScene->AddGameObject(enums::eLayerType::Effect, mPlayerLeftAtt);
			mActiveScene->AddGameObject(enums::eLayerType::Effect, mPlayerRightAtt);
		}
		mActiveScene->SceneIN();

		return iter->second;
	}

}