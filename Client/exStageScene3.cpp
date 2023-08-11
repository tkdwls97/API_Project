#include "exStageScene3.h"
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
#include "exGatekeeper.h"
#include "exThanatos.h"


namespace ex
{
	StageScene3::StageScene3()
	{
	}

	StageScene3::~StageScene3()
	{
	}

	void StageScene3::Initialize()
	{

		GateKeeper* gateKeeper1 = object::Instantiate<GateKeeper>(enums::eLayerType::Monster);
		Transform* gateKeeperTr1 = gateKeeper1->GetComponent<Transform>();
		gateKeeperTr1->SetMoveDir(enums::eMoveDir::Left);
		gateKeeperTr1->SetPosition(math::Vector2(500.0f, 750.0f));
		gateKeeper1->SetMoveDelay(3.0f);
		gateKeeper1->Initialize();

		Thanatos* thanatos1 = object::Instantiate<Thanatos>(enums::eLayerType::Monster);
		Transform* thanatosTr1 = thanatos1->GetComponent<Transform>();
		thanatosTr1->SetMoveDir(enums::eMoveDir::Left);
		thanatosTr1->SetPosition(math::Vector2(180.0f, 750.0f));
		thanatos1->SetMoveDelay(3.0f);
		thanatos1->Initialize();






		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col1 = floor1->AddComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col1->SetSize(math::Vector2(3300.0f, 50.0f));
		tr1->SetPosition(math::Vector2(680.0f, 943.0f));



		// 포탈
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();
		Transform* portalTr = portal->GetComponent<Transform>();
		Animator* portalAt = portal->GetComponent<Animator>();
		Collider* portalCol = portal->GetComponent<Collider>();
		portalAt->SetScale(math::Vector2(0.8f, 0.8f));
		portalTr->SetPosition(math::Vector2(640.0f, 862.0f));
		portalCol->SetSize(math::Vector2(45.0f, 80.0f));

	}

	void StageScene3::Update()
	{
		Scene::Update();
	}

	void StageScene3::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene3::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"Stage3BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage3.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.1f));
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
		playerTF->SetPosition(math::Vector2(400.0f, 800.0f));
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
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
	}
	void StageScene3::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
