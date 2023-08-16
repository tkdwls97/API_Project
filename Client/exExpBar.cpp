#include "exExpBar.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"


namespace ex
{
	ExpBar::ExpBar()
	{
		mExpBar = ResourceManager::Load<Texture>(L"PlayerEmptyExpBar", L"..\\Resources\\Maple\\Image\\UI\\PlayerEmptyExpBar.bmp");

		mAnimator->CreateAnimation(L"PlayerEmptyExpBar", mExpBar, math::Vector2(0.0f, 0.0f), math::Vector2(1000.0f, 13.0f)
			, math::Vector2(1000.0f, 13.0f), 1);
		mTransform->SetPosition(math::Vector2(640.0f, 713.0f));
		mAnimator->SetAffectedCamera(false);
		mAnimator->SetScale(math::Vector2(1.28f, 1.0f));
		mAnimator->PlayAnimation(L"PlayerEmptyExpBar", false);

	}

	ExpBar::~ExpBar()
	{
	}

	void ExpBar::Initialize()
	{
	}

	void ExpBar::Update()
	{
		GameObject::Update();
	}

	void ExpBar::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ExpBar::OnCollisionEnter(Collider* _other)
	{
	}

	void ExpBar::OnCollisionStay(Collider* _other)
	{
	}

	void ExpBar::OnCollisionExit(Collider* _other)
	{
	}
}
