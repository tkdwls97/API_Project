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
#include "exCollider.h"
#include "exCollisionManager.h"
#include "exGreenMush.h"
#include "exCoupleMush.h"
#include "exFloor.h"
#include "exPapulatus.h"
#include "exPortal.h"
#include "exWall.h"
#include "exRope.h"

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
		// ���� �ʷϹ���
		GreenMush* greenMush = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		greenMush->Initialize();

		Transform* grMushtr = greenMush->GetComponent<Transform>();
		grMushtr->SetPosition(math::Vector2(640.0f, 330.0f));


		// ���� Ŀ�� ����
		CoupleMush* coupleMush = object::Instantiate<CoupleMush>(enums::eLayerType::Monster);
		coupleMush->Initialize();

		Transform* cupleMushtr = coupleMush->GetComponent<Transform>();
		cupleMushtr->SetPosition(math::Vector2(800.0f, 360.0f));


		// 1�� �ٴ�
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Transform* floorTr = floor1->GetComponent<Transform>();
		Collider* floorCol = floor1->AddComponent<Collider>();
		floorCol->SetSize(math::Vector2(2000.0f, 50.0f));
		floorTr->SetPosition(math::Vector2(680.0f, 910.0f));

		// 2��
		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol2 = floor2->AddComponent<Collider>();
		Transform* floorTr2 = floor2->GetComponent<Transform>();
		floorCol2->SetSize(math::Vector2(1300.0f, 1.0f));
		floorTr2->SetPosition(math::Vector2(680.0f, 645.0f));

		// 3��
		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol3 = floor3->AddComponent<Collider>();
		Transform* floorTr3 = floor3->GetComponent<Transform>();
		floorCol3->SetSize(math::Vector2(1100.0f, 1.0f));
		floorTr3->SetPosition(math::Vector2(680.0f, 405.0f));

		// 4��
		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol4 = floor4->AddComponent<Collider>();
		Transform* floorTr4 = floor4->GetComponent<Transform>();
		floorCol4->SetSize(math::Vector2(950.0f, 1.0f));
		floorTr4->SetPosition(math::Vector2(680.0f, 165.0f));

		// 5��
		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* floorCol5 = floor5->AddComponent<Collider>();
		Transform* floorTr5 = floor5->GetComponent<Transform>();
		floorCol5->SetSize(math::Vector2(760.0f, 1.0f));
		floorTr5->SetPosition(math::Vector2(680.0f, -75.0f));

		//	// ���� ��
		//	Wall* wall = object::Instantiate<Wall>(enums::eLayerType::Wall);
		//	col = wall->AddComponent<Collider>();
		//	col->SetSize(math::Vector2(10.0f, 1500.0f));
		//	tr = wall->GetComponent<Transform>();
		//	tr->SetPosition(math::Vector2(-237.0f, 360.0f));

		// 1�� -> 2�� ����
		Rope* rope = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope->Initialize();
		Collider* RopeCol = rope->GetComponent<Collider>();
		RopeCol->SetSize(math::Vector2(1.0f, 194.0f));
		Transform* RopeTr = rope->GetComponent<Transform>();
		RopeTr->SetPosition(math::Vector2(393.0f, 737.0f));

		// ��Ż
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		portalTr->SetPosition(math::Vector2(800.0f, 600.0f));
		//potalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
	}

	void StageScene::Update()
	{
		Scene::Update();

	}

	void StageScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}
	void StageScene::SceneIN()
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

		//ī�޶� ��׶��� ������ ���������ϰ� ����
		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);


		// �÷��̾� static���� SceneManager���� �Ѱ��� ����
		Player* player = SceneManager::GetPlayer();

		// ���ӿ�����Ʈ�� �����ڿ��� AddComponent<Transform>()�� ������
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(640.0f, 500.0f));
		Animator* playerAt = player->GetComponent<Animator>();

		// ī�޶��� ������ true || false
		playerAt->SetAffectedCamera(true);

		// ���� ���� ī�޶� Ÿ�� �÷��̾����� ����
		Camera::SetTarget(player);

		// ���� ���� �浹üũ ����
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Wall, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
	}

	void StageScene::SceneOut()
	{
		// ������ ���ö� ī�޶� Ÿ�� �ʱ�ȭ
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
