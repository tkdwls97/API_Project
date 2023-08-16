#include "exSceneManager.h"
#include "exTitleScene.h"
#include "exStageScene.h"
#include "exInput.h"
#include "exBossScene.h"
#include "exStageScene2.h"
#include "exStageScene3.h"
#include "exMushMomScene.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exPlayerAttack.h"
#include "exStatusBar.h"
#include "exExpBar.h"
#include "exHpBar.h"
#include "exMpBar.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;
	PlayerAttack* SceneManager::mPlayerAtt = new PlayerAttack(mPlayer);
	StatusBar* SceneManager::mStatusBar = new StatusBar;
	ExpBar* SceneManager::mExpBar = new ExpBar;
	HpBar* SceneManager::mHpBar = new HpBar;
	MpBar* SceneManager::mMpBar = new MpBar;
	

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<MushMomScene>(L"MushMomScene");
		CreateScene<StageScene2>(L"Stage2Scene");
		CreateScene<StageScene3>(L"Stage3Scene");
		CreateScene<BossScene>(L"BossScene");
		mPlayer->Initialize();
		mPlayerAtt->Initialize();

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
			mActiveScene->AddGameObject(enums::eLayerType::Effect, mPlayerAtt);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mStatusBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mExpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mHpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mMpBar);
		}
		mActiveScene->SceneIN();

		return iter->second;
	}

}