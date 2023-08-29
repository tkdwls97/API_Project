#include "exComboSynergyEffect.h"
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
	ComboSynergyEffect::ComboSynergyEffect(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		//// png
		Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_0"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_000.png");

		mAnimator->CreateAnimation(L"ComboSynergyEffect_0", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);

		mAnimator->CreateAnimation(L"ComboSynergyEffect_1", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);

		mAnimator->CreateAnimation(L"ComboSynergyEffect_2", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);

		mAnimator->CreateAnimation(L"ComboSynergyEffect_3", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);

		mAnimator->CreateAnimation(L"ComboSynergyEffect_4", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
			, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);


		mAnimator->SetScale(math::Vector2(1.0f, 1.0f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		if (playerDir == enums::eMoveDir::Left)
		{
			//mTransform->SetPosition(math::Vector2(playerPos.x + 100.0f, playerPos.y + 20.0f));
		}
		else
		{
			//mTransform->SetPosition(math::Vector2(playerPos.x - 120.0f, playerPos.y + 20.0f));
		}
	}

	ComboSynergyEffect::~ComboSynergyEffect()
	{
	}

	void ComboSynergyEffect::Initialize()
	{
	}

	void ComboSynergyEffect::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void ComboSynergyEffect::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboSynergyEffect::OnCollisionEnter(Collider* _other)
	{
	}

	void ComboSynergyEffect::OnCollisionStay(Collider* _other)
	{
	}

	void ComboSynergyEffect::OnCollisionExit(Collider* _other)
	{
	}
}