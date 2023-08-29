#include "exComboSynergyBody.h"
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
#include "exSound.h"

namespace ex
{
	ComboSynergyBody::ComboSynergyBody(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();


		//// png
		Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyBody"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Body\\ComboSynergy_Body.png");

		mAnimator->CreateAnimation(L"ComboSynergyBody", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);


		mAnimator->SetScale(math::Vector2(0.65f, 0.65f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		if (playerDir == enums::eMoveDir::Left)
		{
			mTransform->SetPosition(math::Vector2(playerPos.x + 100.0f, playerPos.y + 20.0f));
			mAnimator->PlayAnimation(L"LeftComboSynergy", false);
		}
		else
		{
			mTransform->SetPosition(math::Vector2(playerPos.x - 120.0f, playerPos.y + 20.0f));
			mAnimator->PlayAnimation(L"RightComboSynergy", false);
		}
	}

	ComboSynergyBody::~ComboSynergyBody()
	{
	}

	void ComboSynergyBody::Initialize()
	{
	}

	void ComboSynergyBody::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void ComboSynergyBody::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboSynergyBody::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboSynergyBody::OnCollisionStay(Collider* _other)
	{
	}

	void ComboSynergyBody::OnCollisionExit(Collider* _other)
	{
	}
}