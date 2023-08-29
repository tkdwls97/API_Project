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
	ComboSynergyEffect::ComboSynergyEffect(UINT _type)
		: EffectManger(SceneManager::GetPlayer())
		, mOwner(SceneManager::GetPlayer())
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();


		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		//// png
		if (_type == 0)
		{
			Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_0"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_000.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_0", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_0", false);
			//mTransform->SetPosition(playerPos.x - 18.0f, playerPos.y - 50.0f);

		}
		else if (_type == 1)
		{
			Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_1"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_001.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_1", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_1", false);
		}
		else if (_type == 2)
		{
			Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_2"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_002.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_2", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_2", false);
		}

		else if (_type == 3)
		{
			Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_3"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_003.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_3", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_3", false);
		}
		else
		{
			Texture* image = ResourceManager::Load<Texture>(L"ComboSynergyEffect_4"
				, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboSynergy\\Effect\\ComboSynergy_004.png");
			mAnimator->CreateAnimation(L"ComboSynergyEffect_4", image, math::Vector2(0.0f, 0.0f), math::Vector2(111.0f, 112.0f)
				, math::Vector2(111.0f, 112.0f), 1, math::Vector2(0), 0.1f);
			mAnimator->PlayAnimation(L"ComboSynergyEffect_4", false);
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
		Player* player = SceneManager::GetPlayer();
		math::Vector2 playerPos = player->GetPosition();

		bool bCheck = player->IsBuffCheck();
		if (bCheck == false)
		{
			Destroy(this);
		}
		else
		{
			mTransform->SetPosition(playerPos.x - 15.5f, playerPos.y - 45.0f);
			//mAnimator->PlayAnimation(L"ComboSynergyBody", false);
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