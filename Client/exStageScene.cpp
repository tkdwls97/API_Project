#include "exStageScene.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exGameObject.h"
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
		// ��׶���
		Texture* image = ResourceManager::Load<Texture>(L"Stage1BackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Map\\Stage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.0f, 1.0f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));


		// ����1 �ʷϹ���
		GreenMush* greenMush = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		greenMush->Initialize();

		Transform* grMushtr = greenMush->GetComponent<Transform>();
		Animator* grMushat = greenMush->GetComponent<Animator>();
		grMushtr->SetPosition(math::Vector2(640.0f, 360.0f));
		grMushat->SetAffectedCamera(true);
		Collider* moncol = greenMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(55.0f, 70.0f));
		moncol->SetOffset(math::Vector2(5.0f, 4.0f));

		// ����2 Ŀ�� ����
		CupleMush* cupleMush = object::Instantiate<CupleMush>(enums::eLayerType::Monster);
		cupleMush->Initialize();

		Transform* cupleMushtr = cupleMush->GetComponent<Transform>();
		Animator* cupleMushat = cupleMush->GetComponent<Animator>();
		cupleMushat->SetAffectedCamera(true);
		cupleMushtr->SetPosition(math::Vector2(800.0f, 360.0f));
		moncol = cupleMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(100.0f, 70.0f));
		moncol->SetOffset(math::Vector2(4.0f, 4.0f));


		// 1��
		Floor* floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col = floor->GetComponent<Collider>();
		Transform* tr = floor->GetComponent<Transform>();
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(2000.0f, 1.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 880.0f));

		// 2��
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(1300.0f, 1.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 652.0f));

		// 3��
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(1100.0f, 1.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 415.0f));

		// 4��
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(950.0f, 1.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 180.0f));

		// 5��
		floor = object::Instantiate<Floor>(enums::eLayerType::Floor);
		col = floor->AddComponent<Collider>();
		col->SetSize(math::Vector2(760.0f, 30.0f));
		tr = floor->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, -60.0f));


		// ī�޶� ��׶��� ������ ���������ϰ� ����
		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);



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
	void StageScene::SceneIN()
	{

		// �÷��̾� static���� SceneManager���� �Ѱ��� ����
		Player* player = SceneManager::GetPlayer();

		// ���ӿ�����Ʈ�� �����ڿ��� AddComponent<Transform>()�� ������
		Transform* playerTF = player->GetComponent<Transform>();
		playerTF->SetPosition(math::Vector2(-50.0f, 810.0f));
		Animator* playerAt = player->GetComponent<Animator>();

		// ī�޶��� ������ true || false
		playerAt->SetAffectedCamera(true);
		//Collider* playerCol = player->GetComponent<Collider>();
		//playerCol->SetSize(math::Vector2(40.0f, 55.0f));
		//playerCol->SetOffset(math::Vector2(5.0f, 4.0f));

		// ���� ���� ī�޶� Ÿ�� �÷��̾����� ����
		Camera::SetTarget(player);

		// ���� ���� �浹üũ ����
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);

	}

	void StageScene::SceneOut()
	{
		// ������ ���ö� ī�޶� Ÿ�� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
