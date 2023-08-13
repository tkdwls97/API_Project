#include "exMushMomScene.h"
#include "exMushMom.h"
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
#include "exRope.h"
#include "exPlayerFloor.h"

namespace ex
{
	MushMomScene::MushMomScene()
	{
	}

	MushMomScene::~MushMomScene()
	{
	}

	void MushMomScene::Initialize()
	{

		// 680.0f, 763.0f
		MushMom* mushMom = object::Instantiate<MushMom>(enums::eLayerType::Monster);
		Transform* mushMomTr1 = mushMom->GetComponent<Transform>();
		mushMomTr1->SetMoveDir(enums::eMoveDir::Left);
		mushMomTr1->SetPosition(math::Vector2(680.0f, 720.0f));
		mushMom->SetMoveDelay(4.5f);
		mushMom->Initialize();


		//////////////////////////////////////////////////////////////////////
		// ¹Ù´Ú
		// 1Ãþ
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col1 = floor1->GetComponent<Collider>();
		Transform* tr1 = floor1->GetComponent<Transform>();
		col1 = floor1->AddComponent<Collider>();
		col1->SetSize(math::Vector2(2300.0f, 50.0f));
		tr1 = floor1->GetComponent<Transform>();
		tr1->SetPosition(math::Vector2(680.0f, 763.0f));

		// 2Ãþ
		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col2 = floor2->GetComponent<Collider>();
		Transform* tr2 = floor2->GetComponent<Transform>();
		col2 = floor2->AddComponent<Collider>();
		col2->SetSize(math::Vector2(725.0f, 1.0f));
		tr2 = floor2->GetComponent<Transform>();
		tr2->SetPosition(math::Vector2(683.0f, 438.0f));

		// ¿ÞÂÊ 2Ãþ
		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col3 = floor3->GetComponent<Collider>();
		Transform* tr3 = floor3->GetComponent<Transform>();
		col3 = floor3->AddComponent<Collider>();
		col3->SetSize(math::Vector2(480.0f, 1.0f));
		tr3 = floor3->GetComponent<Transform>();
		tr3->SetPosition(math::Vector2(14.0f, 500.0f));

		// Áß¾Ó 3Ãþ
		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col4 = floor4->GetComponent<Collider>();
		Transform* tr4 = floor4->GetComponent<Transform>();
		col4 = floor4->AddComponent<Collider>();
		col4->SetSize(math::Vector2(507.0f, 1.0f));
		tr4 = floor4->GetComponent<Transform>();
		tr4->SetPosition(math::Vector2(683.0f, 240.0f));

		// Áß¾Ó 4Ãþ
		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col5 = floor5->GetComponent<Collider>();
		Transform* tr5 = floor5->GetComponent<Transform>();
		col5 = floor5->AddComponent<Collider>();
		col5->SetSize(math::Vector2(300.0f, 1.0f));
		tr5 = floor5->GetComponent<Transform>();
		tr5->SetPosition(math::Vector2(683.0f, 40.0f));

		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col6 = floor6->GetComponent<Collider>();
		Transform* tr6 = floor6->GetComponent<Transform>();
		col6 = floor6->AddComponent<Collider>();
		col6->SetSize(math::Vector2(121.0f, 1.0f));
		tr6 = floor6->GetComponent<Transform>();
		tr6->SetPosition(math::Vector2(996.0f, 107.0f));

		Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col7 = floor7->GetComponent<Collider>();
		Transform* tr7 = floor7->GetComponent<Transform>();
		col7 = floor7->AddComponent<Collider>();
		col7->SetSize(math::Vector2(50.0f, 1.0f));
		tr7 = floor7->GetComponent<Transform>();
		tr7->SetPosition(math::Vector2(1040.0f, 240.0f));

		Floor* floor8 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col8 = floor8->GetComponent<Collider>();
		Transform* tr8 = floor8->GetComponent<Transform>();
		col8 = floor8->AddComponent<Collider>();
		col8->SetSize(math::Vector2(450.0f, 1.0f));
		tr8 = floor8->GetComponent<Transform>();
		tr8->SetPosition(math::Vector2(1350.0f, 172.0f));

		Floor* floor9 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		Collider* col9 = floor9->GetComponent<Collider>();
		Transform* tr9 = floor9->GetComponent<Transform>();
		col9 = floor9->AddComponent<Collider>();
		col9->SetSize(math::Vector2(690.0f, 1.0f));
		tr9 = floor9->GetComponent<Transform>();
		tr9->SetPosition(math::Vector2(100.0f, 105.0f));


		//////////////////////////////////////////////////////////////////////
		// ·ÎÇÁ
		//1Ãþ->2Ãþ Áß¾Ó ¿ÞÂÊ 
		Rope* rope1 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope1->Initialize();
		Collider* RopeCol1 = rope1->GetComponent<Collider>();
		RopeCol1->SetSize(math::Vector2(2.0f, 212.0f));
		Transform* RopeTr1 = rope1->GetComponent<Transform>();
		RopeTr1->SetPosition(math::Vector2(474.0f, 538.0f));

		// 1Ãþ->2Ãþ Áß¾Ó ¿À¸¥ÂÊ 
		Rope* rope2 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope2->Initialize();
		Collider* RopeCol2 = rope2->GetComponent<Collider>();
		RopeCol2->SetSize(math::Vector2(2.0f, 212.0f));
		Transform* RopeTr2 = rope2->GetComponent<Transform>();
		RopeTr2->SetPosition(math::Vector2(850.0f, 538.0f));

		// 1Ãþ->2Ãþ ¿ÞÂÊ 
		Rope* rope3 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope3->Initialize();
		Collider* RopeCol3 = rope3->GetComponent<Collider>();
		RopeCol3->SetSize(math::Vector2(2.0f, 148.0f));
		Transform* RopeTr3 = rope3->GetComponent<Transform>();
		RopeTr3->SetPosition(math::Vector2(15.0f, 573.0f));

		// 2Ãþ->3Ãþ Áß¾Ó 
		Rope* rope4 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope4->Initialize();
		Collider* RopeCol4 = rope4->GetComponent<Collider>();
		RopeCol4->SetSize(math::Vector2(2.0f, 108.0f));
		Transform* RopeTr4 = rope4->GetComponent<Transform>();
		RopeTr4->SetPosition(math::Vector2(893.0f, 286.0f));

		// 3Ãþ -> 4Ãþ
		Rope* rope5 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope5->Initialize();
		Collider* RopeCol5 = rope5->GetComponent<Collider>();
		RopeCol5->SetSize(math::Vector2(2.0f, 240.0f));
		Transform* RopeTr5 = rope5->GetComponent<Transform>();
		RopeTr5->SetPosition(math::Vector2(371.0f, 220.0f));

		// 3Ãþ -> 4Ãþ Áß¾Ó
		Rope* rope6 = object::Instantiate<Rope>(enums::eLayerType::Rope);
		rope6->Initialize();
		Collider* RopeCol6 = rope6->GetComponent<Collider>();
		RopeCol6->SetSize(math::Vector2(2.0f, 110.0f));
		Transform* RopeTr6 = rope6->GetComponent<Transform>();
		RopeTr6->SetPosition(math::Vector2(551.0f, 92.0f));



		//////////////////////////////////////////////////////////////////////
		// Æ÷Å»
		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		//potalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
		portalTr->SetPosition(math::Vector2(659.0f, -10.0f));
		
	}

	void MushMomScene::Update()
	{
		math::Vector2 pos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Scene::Update();
	}

	void MushMomScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);
	}

	void MushMomScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"BossStage1"
			, L"..\\Resources\\Maple\\Image\\Map\\BossStage1.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.1f, 1.1f));
		bgsr->SetAffectCamera(true);
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);

		Player* player = SceneManager::GetPlayer();

		// °ÔÀÓ¿ÀºêÁ§Æ®´Â »ý¼ºÀÚ¿¡¼­ AddComponent<Transform>()À» ¼±¾ðÇÔ
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(659.0f, -20.0f));
		// ÇÃ·¹ÀÌ¾î°¡ Áß·ÂÀ» ¹Þ±âÀ§ÇØ 
		//player->GetComponent<Rigidbody>()->SetGround(false);
		SceneManager::GetPlayerFloor()->GetRigidbody()->SetGround(false);
		player->SetState(Player::eState::Idle);

		Animator* playerAt = player->GetComponent<Animator>();
		// Ä«¸Þ¶óÀÇ ¿µÇâÀ» true || false
		playerAt->SetAffectedCamera(true);

		// ¾À¿¡ µé¾î°¥¶§ Ä«¸Þ¶ó Å¸°Ù ÇÃ·¹ÀÌ¾îÇÑÅ× ¼¼ÆÃ
		Camera::SetTarget(player);

		// ¾À¿¡ µé¾î°¥¶§ Ãæµ¹Ã¼Å© ¼¼ÆÃ
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Potal, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Monster, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Rope, true);
		//CollisionManager::CollisionLayerCheck(enums::eLayerType::PlayerFloor, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);

	}

	void MushMomScene::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}



}