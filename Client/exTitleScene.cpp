#include "exTitleScene.h"
#include "exPlayer.h"
#include "exSpriteRenderer.h"
#include "exObject.h"
#include "exInput.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exSound.h"
#include "exBackGround.h"
#include "exTransform.h"
#include "exCamera.h"
#include "exAnimator.h"
#include "exCollisionManager.h"
#include "exFloor.h"
#include "exLogin.h"

namespace ex
{
	TitleScene::TitleScene()
		: mTitleSound(nullptr)
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Initialize()
	{	
	}

	void TitleScene::Update()
	{
		Scene::Update();
		
		bool bLogin = Login::IsLoginCheck();
		if (bLogin)
		{
			SceneManager::LoadScene(L"StageScene");
		}
	}

	void TitleScene::Render(HDC _hdc)
	{
		Scene::Render(_hdc);		
	}
	void TitleScene::SceneIN()
	{
		Texture* image = ResourceManager::Load<Texture>(L"TitleBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Logo\\Title.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.7f, 1.8f));
		bgsr->SetAffectCamera(true);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		mTitleSound = ResourceManager::Load<Sound>(L"TitleSound", L"..\\Resources\\Maple\\Sound\\Stage\\Title.wav");
		mTitleSound->Play(true);

		Login* login = object::Instantiate<Login>(enums::eLayerType::Floor);
		login->Initialize();
		
		Camera::SetTarget(nullptr);
	}
	void TitleScene::SceneOut()
	{
		mTitleSound->Stop(true);
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
