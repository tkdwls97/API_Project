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
		// 템플릿이니까 Texture 타입으로 넣어주고 타이틀 백그라운드 이미지라고 이름을 
		// 설정하고
		// 경로를 두번째 인자로 주었다.
		// 로드 함수를 이제 호출한다.
		Texture* image = ResourceManager::Load<Texture>(L"TitleBackGroundImgae"
			, L"..\\Resources\\Maple\\Image\\Logo\\Title.bmp");

		BackGround* bg = object::Instantiate<BackGround>(enums::eLayerType::Background);
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(math::Vector2(1.7f, 1.8f));
		bgsr->SetAffectCamera(true) ;
		//bgsr->SetAlpha(0.2f);
		bg->GetComponent<Transform>()->SetPosition(math::Vector2(640.0f, 360.0f));

		
	}

	void TitleScene::Update()
	{
		Scene::Update();
		if (Input::GetKeyDown(eKeyCode::Q))
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
		Camera::SetTarget(nullptr);
	}
	void TitleScene::SceneOut()
	{
		Camera::SetTarget(nullptr);
		CollisionManager::Clear();
	}
}
