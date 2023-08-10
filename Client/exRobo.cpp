#include "exRobo.h"
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
	Robo::Robo()
	{
	}

	Robo::~Robo()
	{
	}

	void Robo::Initialize()
	{
		// left
		mAnimator->CreateAnimationFolder(L"RoboLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"RoboLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"RoboLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Hit\\Left");

		mAnimator->CreateAnimationFolder(L"RoboLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Die\\Left");


		// Right
		mAnimator->CreateAnimationFolder(L"RoboRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"RoboRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"RoboRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Hit\\Right");

		mAnimator->CreateAnimationFolder(L"RoboRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\Robo\\Die\\Right");;

		mCollider->SetSize(math::Vector2(80.0f, 92.0f));
		//mCollider->SetOffset(math::Vector2(1.0f, 1.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void Robo::Update()
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

	void Robo::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void Robo::Idle()
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
				mAnimator->PlayAnimation(L"RoboLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"RoboRightIdle", true);
			}
		}
	}

	void Robo::Move()
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
				mAnimator->PlayAnimation(L"RoboLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"RoboRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void Robo::Attack()
	{
	}

	void Robo::Chase()
	{
	}

	void Robo::Hit()
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

	void Robo::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"RoboLeftDead", false);

		}
		else
		{
			mAnimator->PlayAnimation(L"RoboRightDead", false);
		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			Destroy(this);
		}


	}
	void Robo::OnCollisionEnter(Collider* _other)
	{
	}

	void Robo::OnCollisionStay(Collider* _other)
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

	void Robo::OnCollisionExit(Collider* _other)
	{
	}
}