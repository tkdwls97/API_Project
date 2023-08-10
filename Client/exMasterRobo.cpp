#include "exMasterRobo.h"
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
	MasterRobo::MasterRobo()
	{
	}

	MasterRobo::~MasterRobo()
	{
	}

	void MasterRobo::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"MasterRoboLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"MasterRoboLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Die\\Left");


		// Right
		mAnimator->CreateAnimationFolder(L"MasterRoboRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"MasterRoboRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\MasterRobo\\Die\\Right");;

		mCollider->SetSize(math::Vector2(80.0f, 92.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void MasterRobo::Update()
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

	void MasterRobo::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void MasterRobo::Idle()
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
				mAnimator->PlayAnimation(L"MasterRoboLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterRoboRightIdle", true);
			}
		}
	}

	void MasterRobo::Move()
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
				mAnimator->PlayAnimation(L"MasterRoboLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"MasterRoboRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void MasterRobo::Attack()
	{
	}

	void MasterRobo::Chase()
	{
	}

	void MasterRobo::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mDirection = enums::eMoveDir::Right;
		}
		else
		{
			mDirection = enums::eMoveDir::Left;
		}
		mMonsterState = eMonsterState::Dead;
	}

	void MasterRobo::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"MasterRoboLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"MasterRoboRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void MasterRobo::OnCollisionEnter(Collider* _other)
	{
	}

	void MasterRobo::OnCollisionStay(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		if (playerAtt != nullptr)
		{
			std::set<GameObject*>* attList = playerAtt->GetAttackList();

			if (attList->find(this) == attList->end())
			{
				mMonsterState = eMonsterState::Hit;
				attList->insert(this);

			}
		}
		Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		if (raisingblow != nullptr)
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

	void MasterRobo::OnCollisionExit(Collider* _other)
	{
	}
}