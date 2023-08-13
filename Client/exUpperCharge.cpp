#include "exUpperCharge.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"


namespace ex
{
	UpperCharge::UpperCharge(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();


		// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Left\\Left_UpperCharge.png");

		mAnimator->CreateAnimation(L"LeftUpperCharge", image, math::Vector2(0.0f, 0.0f), math::Vector2(604.0f, 604.0f)
			, math::Vector2(604.0f, 604.0f), 14, math::Vector2(0), 0.035f);

		// png
		image = ResourceManager::Load<Texture>(L"RightUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\UpperCharge\\Right\\Right_UpperCharge.png");

		mAnimator->CreateAnimation(L"RightUpperCharge", image, math::Vector2(8456.0f, 0.0f), math::Vector2(604.0f, 604.0f)
			, math::Vector2(-604.0f, 0.0f), 14, math::Vector2(0), 0.035f);

		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		mCollider->SetSize(math::Vector2(150.0f, 150.0f));
		if (playerDir == enums::eMoveDir::Left)
		{
			mTransform->SetPosition(math::Vector2(playerPos.x, playerPos.y - 90.0f));
			mAnimator->PlayAnimation(L"LeftUpperCharge", false);
		}
		else
		{
			mTransform->SetPosition(math::Vector2(playerPos.x, playerPos.y - 90.0f));
			mAnimator->PlayAnimation(L"RightUpperCharge", false);
		}

	}

	UpperCharge::~UpperCharge()
	{
	}

	void UpperCharge::Initialize()
	{
	}

	void UpperCharge::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void UpperCharge::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void UpperCharge::OnCollisionEnter(Collider* _other)
	{
	}

	void UpperCharge::OnCollisionStay(Collider* _other)
	{
	}

	void UpperCharge::OnCollisionExit(Collider* _other)
	{
	}
}