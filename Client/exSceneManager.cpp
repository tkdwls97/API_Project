#include "exSceneManager.h"
#include "exTitleScene.h"
#include "exStageScene.h"
#include "exInput.h"
#include "exBossScene.h"
#include "exStageScene2.h"
#include "exStageScene3.h"
#include "exMushMomScene.h"
#include "exEndScene.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exPlayerAttack.h"
#include "exStatusBar.h"
#include "exExpBar.h"
#include "exHpBar.h"
#include "exMpBar.h"
#include "exDamageManager.h"
#include "exMushMomHpBar.h"
#include "exSkillSlot.h"
#include "exLevel.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;
	StatusBar* SceneManager::mStatusBar = new StatusBar;
	ExpBar* SceneManager::mExpBar = new ExpBar;
	HpBar* SceneManager::mHpBar = new HpBar;
	MpBar* SceneManager::mMpBar = new MpBar;
	SkillSlot* SceneManager::mSkillSlot = new SkillSlot;
	Level* SceneManager::mLevel = new Level;
	bool SceneManager::mbPortalCheck = false;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<StageScene>(L"StageScene");
		CreateScene<MushMomScene>(L"MushMomScene");
		CreateScene<StageScene2>(L"Stage2Scene");
		CreateScene<StageScene3>(L"Stage3Scene");
		CreateScene<BossScene>(L"BossScene");
		CreateScene<EndScene>(L"EndScene");
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

	void SceneManager::Release()
	{

		if (mActiveScene->GetName() == L"TitleScene" || mActiveScene->GetName() == L"EndScene")
		{
			delete mPlayer;
			mPlayer = nullptr;

			delete mStatusBar;
			mStatusBar = nullptr;

			delete mExpBar;
			mExpBar = nullptr;

			delete mHpBar;
			mHpBar = nullptr;

			delete mMpBar;
			mMpBar = nullptr;

			delete mSkillSlot;
			mSkillSlot = nullptr;

			delete mLevel;
			mLevel = nullptr;

		}

		for (auto iter : mScenes)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		mScenes.clear();
	}

	Scene* SceneManager::LoadScene(const std::wstring& _name)
	{
		mActiveScene->SceneOut();

		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(_name);

		mActiveScene->RemoveGameObject(enums::eLayerType::Player, mPlayer);

		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mStatusBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mHpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mMpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mExpBar);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mSkillSlot);
		mActiveScene->RemoveGameObject(enums::eLayerType::UI, mLevel);

		if (iter == mScenes.end())
		{
			return nullptr;
		}

		mActiveScene = iter->second;

		// Å¸ÀÌÆ² ¾À End¾ÀÀÌ ¾Æ´Ï¸é ÇÃ·¹ÀÌ¾î¸¦ ¾À¿¡ ³Ö¾îÁÜ
		if (_name != L"TitleScene" && _name != L"EndScene")
		{
			mActiveScene->AddGameObject(enums::eLayerType::Player, mPlayer);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mStatusBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mExpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mHpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mMpBar);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mSkillSlot);
			mActiveScene->AddGameObject(enums::eLayerType::UI, mLevel);
		}

		mActiveScene->SceneIN();

		return iter->second;
	}

}