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
#include "exFloor.h"
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
		// 바닥 1층
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);

		Collider* col = floor1->GetComponent<Collider>();
		Transform* tr = floor1->GetComponent<Transform>();
		col = floor1->AddComponent<Collider>();
		col->SetSize(math::Vector2(1500.0f, 50.0f));
		tr = floor1->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 603.0f));


	}

	void BossScene::Update()
	{
		Scene::Update();
	}

	void BossScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void BossScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"BossBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage2.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.1f, 1.39f));
		bgsr->SetAffectCamera(true);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		Papulatus* papulatus = object::Instantiate<Papulatus>(enums::eLayerType::Monster);
		papulatus->Initialize();
		Transform* papulatusTr = papulatus->GetComponent<Transform>();
		Animator* papulatusat = papulatus->GetComponent<Animator>();
		papulatusTr->SetPosition(math::Vector2(640.0f, 360.0f));
		papulatusat->SetAffectedCamera(true);

		Player* player = SceneManager::GetPlayer();
		// 게임오브젝트는 생성자에서 AddComponent<Transform>()을 선언함
		Transform* playerTF = player->GetComponent<Transform>();
		playerTF->SetPosition(math::Vector2(400.0f, 300.0f));
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
	void BossScene::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
