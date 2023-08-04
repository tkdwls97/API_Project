#include "exPortal.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exSceneManager.h"
#include "exInput.h"
#include "exCollider.h"
#include "exPlayer.h"

namespace ex
{
	Portal::Portal()
	{
	}
	Portal::~Portal()
	{
	}
	void Portal::Initialize()
	{
		Animator* potalAt = AddComponent<Animator>();

		Texture* image = ResourceManager::Load<Texture>(L"Potal"
			, L"..\\Resources\\Maple\\Image\\Potal\\Potal.bmp");
		potalAt->CreateAnimation(L"Potal", image, math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 142.0f)
			, math::Vector2(104.0f, 142.0f), 8, math::Vector2(0.0f, 0.0f), 0.1f);

		potalAt->PlayAnimation(L"Potal", true);
	}

	void Portal::Update()
	{
		//Animator* potalAt = GetComponent<Animator>();
		//potalAt->PlayAnimation(L"Potal", true);

		GameObject::Update();
	}

	void Portal::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Portal::OnCollisionEnter(Collider* _other)
	{
	}
	void Portal::OnCollisionStay(Collider* _other)
	{
		bool portalState = SceneManager::GetPlayer()->IsPotalState();
		std::wstring ActiveSceneName = SceneManager::GetActiveScene()->GetName();
		if (portalState && Input::GetKeyDown(eKeyCode::Up))
		{
			if (ActiveSceneName == L"StageScene")
			{
				SceneManager::LoadScene(L"StageScene2");
			}
			else if (ActiveSceneName == L"StageScene2")
			{
				SceneManager::LoadScene(L"BossScene");
			}
		}
	}
	void Portal::OnCollisionExit(Collider* _other)
	{
		std::wstring ActiveSceneName = SceneManager::GetActiveScene()->GetName();
		ActiveSceneName.clear();
	}
}