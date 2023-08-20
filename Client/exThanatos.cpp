#include "exThanatos.h"
#include "exInput.h" 
#include "exTime.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"
#include "exTexture.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exDamageManager.h"

// PlayerSkill
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exRush.h"
#include "exUpperCharge.h"
namespace ex
{
	Thanatos::Thanatos()
	{
		mMonstersInfo.mMaxHp = 30000000;
		mMonstersInfo.mHp = 30000000;
		mMonstersInfo.mLevel = 180;
		mMonstersInfo.mDamage = 1212;
	}

	Thanatos::~Thanatos()
	{
	}

	void Thanatos::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"ThanatosLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"ThanatosLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Die\\Left");


		// Right
		mAnimator->CreateAnimationFolder(L"ThanatosRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"ThanatosRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\Thanatos\\Die\\Right");;

		mCollider->SetSize(math::Vector2(140.0f, 180.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;

		mAnimator->PlayAnimation(L"ThanatosRightIdle", true);
	}

	void Thanatos::Update()
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

	void Thanatos::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void Thanatos::Idle()
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
				mAnimator->PlayAnimation(L"ThanatosLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightIdle", true);
			}
		}
	}

	void Thanatos::Move()
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
				mAnimator->PlayAnimation(L"ThanatosLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"ThanatosRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void Thanatos::Attack()
	{
	}

	void Thanatos::Chase()
	{
	}

	void Thanatos::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"ThanatosRightHit", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"ThanatosLeftHit", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
	

		if (playerDir == enums::eMoveDir::Left)
		{
			mDirection = enums::eMoveDir::Right;
		}
		else
		{
			mDirection = enums::eMoveDir::Left;
		}
		if (mMonstersInfo.mHp <= 0)
		{
			mMonsterState = eMonsterState::Dead;
		}
	}

	void Thanatos::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"ThanatosLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"ThanatosRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void Thanatos::OnCollisionEnter(Collider* _other)
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

		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr)
		{
			DamageManager* damage = new DamageManager();
			damage->SetPosition(math::Vector2(player->GetPositionX(), player->GetPositionY() - 28.0f));
			damage->PlayMonsterDamageAnimation(this->GetMonstersInfo().mDamage);

		}
	}

	void Thanatos::OnCollisionStay(Collider* _other)
	{
	}

	void Thanatos::OnCollisionExit(Collider* _other)
	{
	}
}