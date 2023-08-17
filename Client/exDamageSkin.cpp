#include "exDamageSkin.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
#include "exPlayer.h"
#include "exDamageManager.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRush.h"
#include "exUpperCharge.h"


namespace ex
{
	DamageSkin::DamageSkin(int _index)
		: mDamageIndex(_index)
	{
		mDamageArr[0] = ResourceManager::Load<Texture>(L"PlayerDamage_0"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_0.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_0", mDamageArr[0], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[1] = ResourceManager::Load<Texture>(L"PlayerDamage_1"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_1.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_1", mDamageArr[1], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[2] = ResourceManager::Load<Texture>(L"PlayerDamage_2"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_2.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_2", mDamageArr[2], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[3] = ResourceManager::Load<Texture>(L"PlayerDamage_3"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_3.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_3", mDamageArr[3], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[4] = ResourceManager::Load<Texture>(L"PlayerDamage_4"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_4.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_4", mDamageArr[4], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[5] = ResourceManager::Load<Texture>(L"PlayerDamage_5"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_5.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_5", mDamageArr[5], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[6] = ResourceManager::Load<Texture>(L"PlayerDamage_6"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_6.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_6", mDamageArr[6], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[7] = ResourceManager::Load<Texture>(L"PlayerDamage_7"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_7.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_7", mDamageArr[7], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[8] = ResourceManager::Load<Texture>(L"PlayerDamage_8"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_8.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_8", mDamageArr[8], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mDamageArr[9] = ResourceManager::Load<Texture>(L"PlayerDamage_9"
			, L"..\\Resources\\Maple\\Image\\UI\\DamageSkin\\Player\\Player_9.bmp");
		mAnimator->CreateAnimation(L"PlayerDamage_9", mDamageArr[9], math::Vector2(0.0f, 0.0f), math::Vector2(50.0f, 50.0f)
			, math::Vector2(50.0f, 50.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mAnimator->SetScale(0.78f);
		
	}

	DamageSkin::~DamageSkin()
	{
	}

	void DamageSkin::Initialize()
	{
	}



	void DamageSkin::Update()
	{
		mDelay += Time::GetDeltaTime();

		if (mDamageDelay <= mDelay)
		{
			switch (mDamageIndex)
			{
			case 0:
				mAnimator->PlayAnimation(L"PlayerDamage_0", false);
				break;
			case 1:
				mAnimator->PlayAnimation(L"PlayerDamage_1", false);
				break;
			case 2:
				mAnimator->PlayAnimation(L"PlayerDamage_2", false);
				break;
			case 3:
				mAnimator->PlayAnimation(L"PlayerDamage_3", false);
				break;
			case 4:
				mAnimator->PlayAnimation(L"PlayerDamage_4", false);
				break;
			case 5:
				mAnimator->PlayAnimation(L"PlayerDamage_5", false);
				break;
			case 6:
				mAnimator->PlayAnimation(L"PlayerDamage_6", false);
				break;
			case 7:
				mAnimator->PlayAnimation(L"PlayerDamage_7", false);
				break;
			case 8:
				mAnimator->PlayAnimation(L"PlayerDamage_8", false);
				break;
			case 9:
				mAnimator->PlayAnimation(L"PlayerDamage_9", false);
				break;
			default:
				break;
			}

			if (mAnimator->IsActiveAnimationComplete())
			{
				Destroy(this);
			}

		}
	
		UI::Update();
	}

	void DamageSkin::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void DamageSkin::OnCollisionEnter(Collider* _other)
	{
	}

	void DamageSkin::OnCollisionStay(Collider* _other)
	{
	}

	void DamageSkin::OnCollisionExit(Collider* _other)
	{
	}

}
