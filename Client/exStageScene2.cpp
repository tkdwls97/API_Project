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
		// �ٴ� 1��
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);

		Collider* col = floor1->GetComponent<Collider>();
		Transform* tr = floor1->GetComponent<Transform>();
		col = floor1->AddComponent<Collider>();
		col->SetSize(math::Vector2(3000.0f, 50.0f));
		tr = floor1->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(680.0f, 566.0f));

		Portal* portal = object::Instantiate<Portal>(enums::eLayerType::Potal);
		portal->Initialize();

		Transform* portalTr = portal->GetComponent<Transform>();
		Animator* portalAt = portal->GetComponent<Animator>();
		Collider* portalCol = portal->AddComponent<Collider>();
		portalAt->SetScale(math::Vector2(0.8f, 0.8f));
		//potalTr->SetPosition(math::Vector2(1370.0f, 830.0f));
		portalTr->SetPosition(math::Vector2(640.0f, 500.0f));
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
			, L"..\\Resources\\Maple\\Image\\Map\\Stage2.bmp");

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

		// ���ӿ�����Ʈ�� �����ڿ��� AddComponent<Transform>()�� ������
		Transform* playerTF = player->GetComponent<Transform>();
		//playerTF->SetPosition(math::Vector2(50.0f, 810.0f));
		playerTF->SetPosition(math::Vector2(400.0f, 500.0f));
		// �÷��̾ �߷��� �ޱ����� 
		player->GetComponent<Rigidbody>()->SetGround(false);

		Animator* playerAt = player->GetComponent<Animator>();
		// ī�޶��� ������ true || false
		playerAt->SetAffectedCamera(true);

		// ���� ���� ī�޶� Ÿ�� �÷��̾����� ����
		Camera::SetTarget(player);

		// ���� ���� �浹üũ ����
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
