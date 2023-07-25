#include "exStageScene.h"
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
#include "exGameEffect.h"
#include "exCollider.h"
#include "exCollisionManager.h"
#include "exGreenMush.h"
#include "exCupleMush.h"
#include "exFloor.h"
#include "exPapulatus.h"

namespace ex
{

	StageScene::StageScene()
	{
	}

	StageScene::~StageScene()
	{
	}

	void StageScene::Initialize()
	{
		// 백그라운드
		Texture* image = ResourceManager::Load<Texture>(L"Stage1BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		// 플레이어
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->Initialize();

		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(640.0f, 360.0f));
		Animator* at = player->GetComponent<Animator>();
		// 카메라의 영향을 true || false
		at->SetAffectedCamera(true);
		
		// 몬스터1 초록버섯
		GreenMush* greenMush = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		greenMush->Initialize();

		Transform* grMushtr = greenMush->GetComponent<Transform>();
		Animator* grMushat = greenMush->GetComponent<Animator>();
		grMushtr->SetPosition(math::Vector2(640.0f, 360.0f));
		grMushat->SetAffectedCamera(true);
		Collider* moncol = greenMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(55.0f, 70.0f));
		moncol->SetOffset(math::Vector2(5.0f, 4.0f));


		// 몬스터2 커플 버섯
		CupleMush* cupleMush = object::Instantiate<CupleMush>(enums::eLayerType::Monster);
		cupleMush->Initialize();

		Transform* cupleMushtr = cupleMush->GetComponent<Transform>();
		Animator* cupleMushat = cupleMush->GetComponent<Animator>();
		cupleMushat->SetAffectedCamera(true);
		cupleMushtr->SetPosition(math::Vector2(800.0f, 360.0f));
		moncol = cupleMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(100.0f, 70.0f));
		moncol->SetOffset(math::Vector2(4.0f, 4.0f));


		Collider* col = player->AddComponent<Collider>();
		col->SetSize(math::Vector2(50.0f, 70.0f));
		col->SetOffset(math::Vector2(5.0f, 4.0f));

		// 1층
		Floor* floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(2000.0f, 50.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 910.0f));

		// 2층
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(1300.0f, 30.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 652.0f));

		// 3층
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(1100.0f, 30.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 415.0f));
		
		// 4층
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(950.0f, 30.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 180.0f));

		// 5층
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(760.0f, 30.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, -60.0f));

	

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		// 카메라의 Target을 플레이어한테 Set
		Camera::SetTarget(player);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		
	}

	void StageScene::Update()
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

	void StageScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
}
