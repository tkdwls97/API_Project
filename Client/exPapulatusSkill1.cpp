#include "exPapulatusSkill1.h"
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
	PapulatusSkill1::PapulatusSkill1(Papulatus* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
		, mPapulatusSkill1_Damege(0)
		, mPapulatusSkill1_Sound(nullptr)
	{
		mPapulatusSkill1_Info.AttackCount = 4;
		mPapulatusSkill1_Info.DamagePercentage = 0;
		SetEffectInfo(mPapulatusSkill1_Info);

		//mPapulatusSkill1_Sound = ResourceManager::Load<Sound>(L"PapulatusSkill1_Sound", L"..\\Resources\\Maple\\Sound\\Monster\\Papulatus\\Papulatus_Skill1.wav");
		//mPapulatusSkill1_Sound->Play(false);

		mAnimator = _owner->GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		for (size_t i = 0; i < mPapulatusSkill1_Info.AttackCount; i++)
		{
			PapulatusSkillArea* papulatusSkillArea = new PapulatusSkillArea(_owner);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkillArea);
		}

	}

	PapulatusSkill1::~PapulatusSkill1()
	{
	}

	void PapulatusSkill1::Initialize()
	{
	}

	void PapulatusSkill1::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void PapulatusSkill1::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PapulatusSkill1::OnCollisionEnter(Collider* _other)
	{
	}

	void PapulatusSkill1::OnCollisionStay(Collider* _other)
	{
	}

	void PapulatusSkill1::OnCollisionExit(Collider* _other)
	{
	}
}