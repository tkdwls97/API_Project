#include "exTitleScene.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exObject.h"
#include "exInput.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exBackGround.h"
#include "exTransform.h"
#include "exCamera.h"
#include "exAnimator.h"
#include "exCollisionManager.h"

namespace ex
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{
		// ���ø��̴ϱ� Texture Ÿ������ �־��ְ� Ÿ��Ʋ ��׶��� �̹������ �̸��� �����ϰ�
		// ��θ� �ι�° ���ڷ� �־���.
		// �ε� �Լ��� ���� ȣ���Ѵ�.
		Texture* image = ResourceManager::Load<Texture>(L"TitleBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Logo\\Title.bmp");


		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.7f, 1.8f));
		bgsr->SetAffectCamera(true) ;
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		bg->SetAutoCameraLimit();
		math::Vector2 widthLimit = math::Vector2(bg->GetLimitLeft(), bg->GetLimitRight());
		math::Vector2 heightLimit = math::Vector2(bg->GetLimitUp(), bg->GetLimitDown());
		Camera::SetLimitDistance(widthLimit, heightLimit);
	}

	void TitleScene::Update()
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

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);		
	}
	void TitleScene::SceneIN()
	{
		Camera::SetTarget(nullptr);
	}
	void TitleScene::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
