#include "exPotal.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exAnimator.h"

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
			, math::Vector2(104.0f, 142.0f), 8);
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

	void Potal::OnCollisionEnter(Collider* other)
	{
	}
	void Potal::OnCollisionStay(Collider* other)
	{
	}
	void Potal::OnCollisionExit(Collider* other)
	{
	}
}