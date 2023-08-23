#include "exPapulatusSkill3.h"
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
	PapulatusSkill3::PapulatusSkill3(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill3_Damege(0)
		, mPapulatusSkill3_Sound(nullptr)
	{
		mPapulatusSkill3_Info.AttackCount = 1;
		mPapulatusSkill3_Info.DamagePercentage = 9;
		SetEffectInfo(mPapulatusSkill3_Info);

		//mPapulatusSkill3_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill3_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill3.wav");
		//mPapulatusSkill3_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();


	}

	PapulatusSkill3::~PapulatusSkill3()
	{
	}

	void PapulatusSkill3::Initialize()
	{
	}

	void PapulatusSkill3::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill3::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill3::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSkill3::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill3::OnCollisionExit(Collider* _other)
	{
	}
}