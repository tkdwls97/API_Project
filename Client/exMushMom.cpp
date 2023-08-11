#include "exMushMom.h"
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
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exObject.h"

namespace ex
{
	MushMom::MushMom()
	{
	}

	MushMom::~MushMom()
	{
	}

	void MushMom::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"MushMomLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"MushMomLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Move\\Left", math::Vector2(0.0f, -140.0f));

		mAnimator->CreateAnimationFolder(L"MushMomLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Hit\\Left");

		// Right
		mAnimator->CreateAnimationFolder(L"MushMomRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"MushMomRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Move\\Right", math::Vector2(0.0f, -140.0f));

		mAnimator->CreateAnimationFolder(L"MushMomRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\MushMom\\Hit\\Right");

		mAnimator->SetAffectedCamera(true);
		mAnimator->SetScale(math::Vector2(5.0f, 5.0f));
		mCollider->SetSize(math::Vector2(150.0f, 150.0f));
		mCollider->SetOffset(math::Vector2(0.0f, 0.0f));
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}

	void MushMom::Update()
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

	void MushMom::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void MushMom::Idle()
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
				mAnimator->PlayAnimation(L"MushMomLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightIdle", true);
			}
		}
	}

	void MushMom::Move()
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
				mAnimator->PlayAnimation(L"MushMomLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void MushMom::Attack()
	{
	}

	void MushMom::Chase()
	{
	}

	void MushMom::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"MushMomRightHit", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"MushMomLeftHit", false);

		}
		mHitDelay += Time::GetDeltaTime();
		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"MushMomLeftMove", true);
				mMonsterState = eMonsterState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"MushMomRightMove", true);
				mMonsterState = eMonsterState::Move;
			}
			mHitDelay = 0.0f;
		}
		//mMonsterState = eMonsterState::Dead;
	}

	void MushMom::Dead()
	{
		//if (playerDir == enums::eMoveDir::Left)
		//{
		//	mAnimator->PlayAnimation(L"GreenMushRightDead", false);
		//}
		//else
		//{
		//	mAnimator->PlayAnimation(L"GreenMushLeftDead", false);

		//}

		//bool bCheck = mAnimator->IsActiveAnimationComplete();
		//if (bCheck)
		//{
		//	Destroy(this);
		//}
	}
	void MushMom::OnCollisionEnter(Collider* _other)
	{
		//PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		//enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		//if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		//{
		//	// playerAttack이 들고있는 mAttList를 받아서 넣어줌 자신을(파풀라투스)
		//	std::set<GameObject*>* attList = playerAtt->GetAttackList();

		//	if (attList->find(this) == attList->end())
		//	{
		//		mMonsterState = eMonsterState::Hit;
		//		attList->insert(this);
		//	}
		//}
		//Raisingblow* raisingblow = dynamic_cast<Raisingblow*>(_other->GetOwner());
		//if (raisingblow != nullptr)
		//{
		//	std::set<GameObject*>* attList = raisingblow->GetAttackList();

		//	if (attList->find(this) == attList->end())
		//	{
		//		RaisingblowHit* raisingBlowHit = new RaisingblowHit(this);
		//		object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlowHit);
		//		mMonsterState = eMonsterState::Hit;
		//		attList->insert(this);

		//	}
		//}
	}

	void MushMom::OnCollisionStay(Collider* _other)
	{
		PlayerAttack* playerAtt = dynamic_cast<PlayerAttack*>(_other->GetOwner());
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetMoveDir();
		if (playerAtt != nullptr && mMonsterState != eMonsterState::Dead)
		{
			// playerAttack이 들고있는 mAttList를 받아서 넣어줌 자신을(파풀라투스)
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

	void MushMom::OnCollisionExit(Collider* _other)
	{
	}

}