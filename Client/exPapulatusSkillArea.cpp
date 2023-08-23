#include "exPapulatusSkillArea.h"
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
#include "exAnimation.h"
#include "exMonsters.h"
#include "exDamageManager.h"
#include "exPapulatus.h"
#include "exSound.h"
#include "exPapulatusSkillArea.h"

namespace ex
{
	PapulatusSkillArea::PapulatusSkillArea(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkillArea_Info()
		, mPapulatusSkillArea_Sound(nullptr)
	{
		mPapulatusSkillArea_Info.AttackCount = 1;
		mPapulatusSkillArea_Info.DamagePercentage = 9;
		mPapulatusSkillArea_Damege = 398;
		SetEffectInfo(mPapulatusSkillArea_Info);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mAnimator->CreateAnimationFolder(L"PapulatusSkillArea",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Area");

		mAnimator->PlayAnimation(L"PapulatusSkillArea", false);
		mCollider->SetSize(math::Vector2(0.0f, 0.0f));
		int random = rand() % 7 + 1;
		if (random == 1)
		{
			mTransform->SetPosition(math::Vector2(-169.0f, 245.0f));
		}
		else if (random == 2)
		{
			mTransform->SetPosition(math::Vector2(128.0f, 245.0f));
		}
		else if (random == 3)
		{
			mTransform->SetPosition(math::Vector2(454.0f, 245.0f));
		}
		else if (random == 4)
		{
			mTransform->SetPosition(math::Vector2(699.0f, 245.0f));
		}
		else if (random == 5)
		{
			mTransform->SetPosition(math::Vector2(955.0f, 245.0f));
		}
		else if (random == 6)
		{
			mTransform->SetPosition(math::Vector2(1220.0f, 245.0f));
		}
		else if (random == 7)
		{
			mTransform->SetPosition(math::Vector2(1561.0f, 245.0f));
		}

	}

	PapulatusSkillArea::~PapulatusSkillArea()
	{
	}

	void PapulatusSkillArea::Initialize()
	{
	}

	void PapulatusSkillArea::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mCollider->SetSize(math::Vector2(120.0f, 800.0f));
			Destroy(this);
		}
		GameObject::Update();
	}

	void PapulatusSkillArea::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkillArea::OnCollisionEnter(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mPapulatusSkillArea_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void PapulatusSkillArea::OnCollisionStay(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f * i));
				damage->PlayMonsterDamageAnimation(mPapulatusSkillArea_Damege, this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void PapulatusSkillArea::OnCollisionExit(Collider* _other)
	{
	}
}