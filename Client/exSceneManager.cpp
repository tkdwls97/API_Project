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
#include "exPlayerFloor.h"

namespace ex
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScene = nullptr;
	Player* SceneManager::mPlayer = new Player;
	PlayerAttack* SceneManager::mPlayerAtt = new PlayerAttack(mPlayer);
	PlayerFloor* SceneManager::mPlayerFloor = new PlayerFloor(mPlayer);

	
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

		// Ÿ��Ʋ �� End���� �ƴϸ� �÷��̾ ���� �־���
		if (_name != L"TitleScene" && _name != L"EndScene")
		{
			mActiveScene->AddGameObject(enums::eLayerType::Player, mPlayer);
			mActiveScene->AddGameObject(enums::eLayerType::Effect, mPlayerAtt);
			mActiveScene->AddGameObject(enums::eLayerType::PlayerFloor, mPlayerFloor);

		}
		mActiveScene->SceneIN();

		return iter->second;
	}

}