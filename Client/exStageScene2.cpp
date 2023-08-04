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
#include "exPortal.h"
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
		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);

		Collider* col = floor1->GetComponent<Collider>();
		Transform* tr = floor1->GetComponent<Transform>();
		col = floor1->AddComponent<Collider>();
		col->SetSize(math::Vector2(3000.0f, 50.0f));
		tr = floor1->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 730.0f));


		// 바닥 2층
		//Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);

		//Collider* col = floor2->GetComponent<Collider>();
		//Transform* tr = floor2->GetComponent<Transform>();
		//col = floor2->AddComponent<Collider>();
		//col->SetSize(math::Vector2(2000.0f, 50.0f));
		//tr = floor2->GetComponent<Transform>();
		//tr->SetPosition(math::Vector2(680.0f, 685.0f));


		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		Animator* portalAt = portal->GetComponent<Animator>();
		Collider* portalCol = portal->AddComponent<Collider>();
		portalAt->SetScale(math::Vector2(0.8f, 0.8f));
		//potalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
		portalTr->SetPosition(math::Vector2(640.0f, 650.0f));
		portalCol->SetSize(math::Vector2(45.0f, 80.0f));

	}

	void StageScene2::Update()
	{
		Scene::Update();
	}

	void StageScene2::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene2::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Stage2BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		Player* player = SceneManager::GetPlayer();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(400.0f, 600.0f));
		// 플레이어가 중력을 받기위해 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		playerAt->SetAffectedCamera(true);

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
