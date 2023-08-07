#include "exPortal.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exSceneManager.h"
#include "exInput.h"
#include "exCollider.h"
#include "exPlayer.h"
#include "exTransform.h"

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

		Texture* image = ResourceManager::Load<Texture>(L"Potal"
			, L"..\\Resources\\Maple\\Image\\Potal\\Potal.bmp");

		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mAnimator->CreateAnimation(L"Potal", image, math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 142.0f)
			, math::Vector2(104.0f, 142.0f), 8, math::Vector2(0.0f, 0.0f), 0.1f);
		
		// 포탈 collider 사이즈 설정
		mCollider->SetSize(math::Vector2(45.0f, 80.0f));
		// 포탈 스케일 설정
		mAnimator->SetScale(math::Vector2(0.8f, 0.8f));

		mAnimator->PlayAnimation(L"Potal", true);
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
				SceneManager::LoadScene(L"MushMomScene");
			}
			else if (ActiveSceneName == L"MushMomScene")
			{
				SceneManager::LoadScene(L"Stage2Scene");
			}
			else if (ActiveSceneName == L"Stage2Scene")
			{
				SceneManager::LoadScene(L"Stage3Scene");
			}
			else if (ActiveSceneName == L"Stage3Scene")
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