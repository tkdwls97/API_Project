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
#include "exPapulatus.h"
#include "exCollisionManager.h"

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
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.1f, 1.4f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

	
		/*bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);*/
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
	void BossScene::SceneIN()
	{
		Papulatus* papulatus = object::Instantiate<Papulatus>(enums::eLayerType::Monster);
		papulatus->Initialize();
		Transform* papulatusTr = papulatus->GetComponent<Transform>();
		Animator* papulatusat = papulatus->GetComponent<Animator>();
		papulatusTr->SetPosition(math::Vector2(640.0f, 360.0f));
		papulatusat->SetAffectedCamera(true);
		Camera::SetTarget(papulatus);
	}
	void BossScene::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
