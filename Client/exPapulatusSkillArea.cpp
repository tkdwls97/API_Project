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

		//PapulatusSkillArea_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill1_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill1.wav");
		//PapulatusSkillArea_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		mAnimator->CreateAnimationFolder(L"PapulatusSkillArea",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Area");

		mAnimator->PlayAnimation(L"PapulatusSkillArea", true);


		// 맵 사이즈 안에서 랜덤 위치에 설정
		//mTransform->


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
	}

	void PapulatusSkillArea::OnCollisionExit(Collider* _other)
	{
	}
}