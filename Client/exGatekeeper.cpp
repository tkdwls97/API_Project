#include "exGateKeeper.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exCollider.h"
#include "exPlayerAttack.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"

namespace ex
{
	GateKeeper::GateKeeper()
	{
	}

	GateKeeper::~GateKeeper()
	{
	}

	void GateKeeper::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"GateKeeperLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"GateKeeperLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Die\\Left");


		// Right
		mAnimator->CreateAnimationFolder(L"GateKeeperRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"GateKeeperRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Ability\\GateKeeper\\Die\\Right");;

		mCollider->SetSize(math::Vector2(120.0f, 120.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;

		mAnimator->PlayAnimation(L"GateKeeperLeftIdle", true);
	}

	void GateKeeper::Update()
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

	void GateKeeper::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void GateKeeper::Idle()
	{
		//mIdleDelay += Time::GetDeltaTime();

		//math::Vector2 pos = mTransform->GetPosition();
		//if (mIdleDelay >= 2.3f)
		//{
		//	if (mDirection == enums::eMoveDir::Left)
		//	{
		//		mDirection = enums::eMoveDir::Right;
		//	}
		//	else
		//	{
		//		mDirection = enums::eMoveDir::Left;
		//	}
		//	mMonsterState = eMonsterState::Move;
		//	mIdleDelay = 0.0f;
		//}
		//else
		//{
		//	if (mDirection == enums::eMoveDir::Left)
		//	{
		//		mAnimator->PlayAnimation(L"GateKeeperLeftIdle", true);
		//	}
		//	else
		//	{
		//		mAnimator->PlayAnimation(L"GateKeeperRightIdle", true);
		//	}
		//}
	}

	void GateKeeper::Move()
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
				mAnimator->PlayAnimation(L"GateKeeperLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"GateKeeperRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void GateKeeper::Attack()
	{
	}

	void GateKeeper::Chase()
	{
	}

	void GateKeeper::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"GateKeeperRightHit", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"GateKeeperLeftHit", false);

		}
		if (playerDir == enums::eMoveDir::Left)
		{
			mDirection = enums::eMoveDir::Right;
		}
		else
		{
			mDirection = enums::eMoveDir::Left;
		}


		//mMonsterState = eMonsterState::Dead;
	}

	void GateKeeper::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"GateKeeperLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"GateKeeperRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void GateKeeper::OnCollisionEnter(Collider* _other)
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
	}

	void GateKeeper::OnCollisionStay(Collider* _other)
	{
	}

	void GateKeeper::OnCollisionExit(Collider* _other)
	{
	}
}