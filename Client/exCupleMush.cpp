#include "exCupleMush.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"


namespace ex
{
	CupleMush::CupleMush()
	{
	}

	CupleMush::~CupleMush()
	{
	}

	void CupleMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"CoupleMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\CoupleMush_LEFT.bmp");

		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(L"CoupleMushLeftIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 8);
		animator->CreateAnimation(L"CoupleMushLeftMove", image, math::Vector2(170.0f, 170.0f), math::Vector2(170.0f,170.0f)
			, math::Vector2(170.0f, 170.0f), 13);

		image = ResourceManager::Load<Texture>(L"CoupleMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\CoupleMush_RIGHT.bmp");

		animator->CreateAnimation(L"CoupleMushRightIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 8);
		animator->CreateAnimation(L"CoupleMushRightMove", image, math::Vector2(170.0f, 170.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 13);

		animator->PlayAnimation(L"CoupleMushRightIdle", true);

		GetTransform()->SetMoveDir(enums::eMoveDir::Right);
	}

	void CupleMush::Update()
	{
		GameObject::Update();



	}

	void CupleMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void CupleMush::OnCollisionEnter(Collider* other)
	{
	}

	void CupleMush::OnCollisionStay(Collider* other)
	{
	}

	void CupleMush::OnCollisionExit(Collider* other)
	{
	}

}