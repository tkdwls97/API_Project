#include "exPotal.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exSceneManager.h"
#include "exInput.h"
#include "exCollider.h"

namespace ex
{
	Potal::Potal()
	{
	}
	Potal::~Potal()
	{
	}
	void Potal::Initialize()
	{
		Animator* potalAt = AddComponent<Animator>();

		Texture* image = ResourceManager::Load<Texture>(L"Potal"
			, L"..\\Resources\\Maple\\Image\\Potal\\Potal.bmp");
		potalAt->CreateAnimation(L"Potal", image, math::Vector2(0.0f, 0.0f), math::Vector2(104.0f, 142.0f)
			, math::Vector2(104.0f, 142.0f), 8, math::Vector2(0.0f, 0.0f), 0.16f);
	}

	void Potal::Update()
	{
		Animator* potalAt = GetComponent<Animator>();
		potalAt->PlayAnimation(L"Potal", true);

		GameObject::Update();
	}

	void Potal::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Potal::OnCollisionEnter(Collider* _other)
	{
	}
	void Potal::OnCollisionStay(Collider* _other)
	{
		// 다이나믹 캐스트로 변경해야함

		if (Type == enums::eLayerType::Player && Input::GetKeyDown(eKeyCode::Up))
		{
			if (activeScene->GetName() == L"StageScene")
			{
				SceneManager::LoadScene(L"StageScene2");
			}
		}
		else if (Type == enums::eLayerType::Player && activeScene->GetName() == L"StageScene2")
		{
			if (Input::GetKeyDown(eKeyCode::Up))
			{
				SceneManager::LoadScene(L"BossScene");
			}
		}
	}
	void Potal::OnCollisionExit(Collider* _other)
	{
	}
}