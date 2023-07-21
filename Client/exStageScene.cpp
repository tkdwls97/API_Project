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
#include "exMonsterObject.h"
#include "exGameEffect.h"
#include "exCollider.h"
#include "exCollisionManager.h"


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

		// �÷��̾�
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->Initialize();

		// ���ӿ�����Ʈ�� �����ڿ��� AddComponent<Transform>()�� ������
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(math::Vector2(640.0f, 360.0f));
		Animator* at = player->AddComponent<Animator>();
		

		// ����1 �ʷϹ���
		GreenMush* greenMush = object::Instantiate<GreenMush>(enums::eLayerType::Monster);
		greenMush->Initialize();

		Transform* grMushtr = greenMush->GetComponent<Transform>();
		Animator* grMushat = greenMush->AddComponent<Animator>();
		grMushtr->SetPosition(math::Vector2(640.0f, 360.0f));
		grMushat->SetAffectedCamera(true);
		Collider* moncol = greenMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(55.0f, 70.0f));
		moncol->SetOffset(math::Vector2(5.0f, 4.0f));


		// ����2 Ŀ�� ����
		CupleMush* cupleMush = object::Instantiate<CupleMush>(enums::eLayerType::Monster);
		cupleMush->Initialize();

		Transform* cupleMushtr = cupleMush->GetComponent<Transform>();
		Animator* cupleMushat = cupleMush->AddComponent<Animator>();
		cupleMushat->SetAffectedCamera(true);
		cupleMushtr->SetPosition(math::Vector2(800.0f, 360.0f));
		moncol = cupleMush->AddComponent<Collider>();
		moncol->SetSize(math::Vector2(100.0f, 70.0f));
		moncol->SetOffset(math::Vector2(4.0f, 4.0f));
		


		// ī�޶��� ������ true || false
		at->SetAffectedCamera(true);

		// ī�޶��� Target�� �÷��̾����� Set
		Camera::SetTarget(player);

		Collider* col = player->AddComponent<Collider>();
		col->SetSize(math::Vector2(50.0f, 70.0f));
		col->SetOffset(math::Vector2(5.0f, 4.0f));

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		
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
