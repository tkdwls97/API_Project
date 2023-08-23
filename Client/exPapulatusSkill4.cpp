#include "exPapulatusSkill4.h"
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
	PapulatusSkill4::PapulatusSkill4(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill4_Damege(0)
		, mPapulatusSkill4_Sound(nullptr)
	{
		mPapulatusSkill4_Info.AttackCount = 3;
		mPapulatusSkill4_Info.DamagePercentage = 0;
		SetEffectInfo(mPapulatusSkill4_Info);

		//mPapulatusSkill4_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill4_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill4.wav");
		//mPapulatusSkill4_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();



	}

	PapulatusSkill4::~PapulatusSkill4()
	{
	}

	void PapulatusSkill4::Initialize()
	{
	}

	void PapulatusSkill4::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill4::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill4::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSkill4::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill4::OnCollisionExit(Collider* _other)
	{
	}
}