#include "exBossScene.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exInput.h"
#include "exTexture.h"
#include "exTransform.h"
#include "exResourceManager.h"
#include "exBackGround.h"
#include "exCamera.h"
#include "exAnimator.h"

namespace ex
{

	BossScene::BossScene()
	{
	}

	BossScene::~BossScene()
	{
	}

	void BossScene::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"BossBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage.png");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		//Camera::SetTarget(player);
	}

	void BossScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::Q))
		{
			SceneManager::LoadScene(L"StageScene");
		}
		if (Input::GetKeyDown(eKeyCode::W))
		{
			SceneManager::LoadScene(L"StageScene2");
		}

		if (Input::GetKeyDown(eKeyCode::E))
		{
			SceneManager::LoadScene(L"BossScene");
		}
		if (Input::GetKeyDown(eKeyCode::R))
		{
			SceneManager::LoadScene(L"VillageScene");
		}
		if (Input::GetKeyDown(eKeyCode::T))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}

	void BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
}
