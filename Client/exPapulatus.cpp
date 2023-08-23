#include "exPapulatus.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exSceneManager.h"
#include "exPlayer.h"
#include "exObject.h"
#include "exDamageManager.h"
#include "exFloor.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
#include "exComboDeathFaultScreen.h"


namespace ex
{
	Papulatus::Papulatus()
		: mbPapulatusHit(false)
		, mAttackDelay(0.0f)
		, mSkill1Damage(0)
		, mSkill2Damage(0)
		, mSkill3Damage(0)
	{
		mMonstersInfo.mMaxHp = 700000000;
		mMonstersInfo.mHp = 700000000;
		mMonstersInfo.mLevel = 190;
		mMonstersInfo.mDamage = 750;
		mSkill1Damage = 411;
		mSkill2Damage = 403;
		mSkill3Damage = 380;
	}

	Papulatus::~Papulatus()
	{
	}

	void Papulatus::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"PapulatusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Left", math::Vector2(0.0f,-40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Left", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Left", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Left", math::Vector2(0.0f, -40.0f));

		// Left Skill
		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Left", math::Vector2(0.0f, -40.0f));
		
		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Left", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Left", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Left", math::Vector2(0.0f, -40.0f));

		// Right
		mAnimator->CreateAnimationFolder(L"PapulatusRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Right", math::Vector2(0.0f, -40.0f));

		//Right Skill
		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Right", math::Vector2(0.0f, -40.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Right", math::Vector2(0.0f, -40.0f));


		mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
		mTransform->SetMoveDir(enums::eMoveDir::Left);

		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(math::Vector2(250.0f, 120.0f));
		mCollider->SetOffset(math::Vector2(0.0f, 0.0f));
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void Papulatus::Update()
	{
		switch (mMonsterState)
		{
		case ex::Monsters::eMonsterState::Idle:
			Idle();
			break;
		case ex::Monsters::eMonsterState::Move:
			Move();
			break;
		case ex::Monsters::eMonsterState::Attack:
			Attack();
			break;
		case ex::Monsters::eMonsterState::Chase:
			Chase();
			break;
		case ex::Monsters::eMonsterState::Hit:
			Hit();
			break;
		case ex::Monsters::eMonsterState::Dead:
			Dead();
			break;
		default:
			break;
		}


		GameObject::Update();
	}

	void Papulatus::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Papulatus::Idle()
	{
		mIdleDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mIdleDelay >= 2.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mDirection = enums::eMoveDir::Right;
			}
			else
			{
				mDirection = enums::eMoveDir::Left;
			}
			mMonsterState = eMonsterState::Move;
			mIdleDelay = 0.0f;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightIdle", true);
			}
		}
	}

	void Papulatus::Move()
	{
		mMoveTime -= Time::GetDeltaTime();
		math::Vector2 pos = mTransform->GetPosition();
		if (mMoveTime <= 0.0f)
		{
			mMonsterState = eMonsterState::Idle;
			mMoveTime = mMoveDelay;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void Papulatus::Attack()
	{
	}

	void Papulatus::Chase()
	{
	}

	void Papulatus::Hit()
	{
		mbPapulatusHit = true;
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PapulatusRightHit", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusLeftHit", false);

		}
		mHitDelay += Time::GetDeltaTime();
		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				mMonsterState = eMonsterState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mMonsterState = eMonsterState::Move;
			}
			mHitDelay = 0.0f;
		}
		if (mMonstersInfo.mHp <= 0)
		{
			mMonsterState = eMonsterState::Dead;
		}
	}

	void Papulatus::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PapulatusLeftDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}
	}

	void Papulatus::Skill1()
	{
	}

	void Papulatus::Skill2()
	{
	}

	void Papulatus::Skill3()
	{
	}

	void Papulatus::Skill4()
	{
	}

	void Papulatus::OnCollisionEnter(Collider* _other)
	{

		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		if (raisingblow != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = raisingblow->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);
			}
		}

		UpperCharge* upperCharge = dynamic_cast<UpperCharge*>(_other->GetOwner());
		if (upperCharge != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = upperCharge->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		Rush* rush = dynamic_cast<Rush*>(_other->GetOwner());
		if (rush != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = rush->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}

		ComboDeathFaultScreen* ComboDeathFault = dynamic_cast<ComboDeathFaultScreen*>(_other->GetOwner());
		if (ComboDeathFault != nullptr && mMonsterState != eMonsterState::Dead)
		{
			std::set<GameObject*>* attList = ComboDeathFault->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);
			}
		}

		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->IsInvincible() == false)
		{
			DamageManager* damage = new DamageManager();
			damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f));
			damage->PlayMonsterDamageAnimation(this->GetMonstersInfo().mDamage);

		}
	}

	void Papulatus::OnCollisionStay(Collider* _other)
	{
	}

	void Papulatus::OnCollisionExit(Collider* _other)
	{
	}

}