#include "exStageScene2.h"
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
#include "exCollisionManager.h"
#include "exFloor.h"
#include "exPotal.h"
namespace ex
{
	StageScene2::StageScene2()
	{
	}

	StageScene2::~StageScene2()
	{
	}

	void StageScene2::Initialize()
	{

		//Texture* image = ResourceManager::Load<Texture>(L"Stage2BackGroundImgae"
		//	, L"..\\Resources\\Maple\\Image\\Map\\Stage2.bmp");

		//BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		//SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		//bgsr->SetImage(image);
		//bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		//bgsr->SetAffectCamera(true);
		////bgsr->SetAlpha(0.2f);
		//bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		Floor* floor = object::Instantiate<Floor>(enums::eLayerType::Floor);

		Collider* col = floor->GetComponent<Collider>();
		Transform* tr = floor->GetComponent<Transform>();
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(2000.0f, 50.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 685.0f));


		Potal* potal = object::Instantiate<Potal>(enums::eLayerType::Potal);
		potal->Initialize();

		Transform* potalTr = potal->GetComponent<Transform>();
		Animator* potalAt = potal->GetComponent<Animator>();
		Collider* potalCol = potal->AddComponent<Collider>();
		potalAt->SetScale(math::Vector2(0.8f, 0.8f));
		//potalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
		potalTr->SetPosition(math::Vector2(640.0f, 630.0f));
		potalCol->SetSize(math::Vector2(45.0f, 80.0f));
		
		//bg->SetAutoCameraLimit();
		//math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		//math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		//Camera::SetLimitDistance(widthLimit, heightLimit);

	}

	void StageScene2::Update()
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

	void StageScene2::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene2::SceneIN()
	{
		Player* player = SceneManager::GetPlayer();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(640.0f, 500.0f));
		Animator* playerAt = player->GetComponent<Animator>();

		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);
		//Collider* playerCol = player->GetComponent<Collider>();
		//playerCol->SetSize(math::Vector2(40.0f, 55.0f));
		//playerCol->SetOffset(math::Vector2(5.0f, 4.0f));

		// 씬에 들어갈때 카메라 타겟 플레이어한테 세팅
		Camera::SetTarget(player);

		// 씬에 들어갈때 충돌체크 세팅
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
	}
	void StageScene2::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
