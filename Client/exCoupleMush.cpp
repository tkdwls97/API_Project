#include "exCoupleMush.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exAnimator.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exSceneManager.h"
#include "exPlayerAttack.h"
#include "exPlayer.h"

namespace ex
{
	CoupleMush::CoupleMush()
		 : mIdleDelay(0.0f)
	     , mMoveDelay(0.0f)
	{
	}

	CoupleMush::~CoupleMush()
	{
	}

	void CoupleMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"CoupleMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\CoupleMush_LEFT.bmp");

		mAnimator->CreateAnimation(L"CoupleMushLeftIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 8);
		mAnimator->CreateAnimation(L"CoupleMushLeftMove", image, math::Vector2(170.0f, 170.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 14);
		mAnimator->CreateAnimation(L"CoupleMushLeftDead", image, math::Vector2(510.0f, 170.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(510.0f, 170.0f), 5);

		image = ResourceManager::Load<Texture>(L"CoupleMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\CoupleMush_RIGHT.bmp");

		mAnimator->CreateAnimation(L"CoupleMushRightIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 8);
		mAnimator->CreateAnimation(L"CoupleMushRightMove", image, math::Vector2(170.0f, 170.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(170.0f, 170.0f), 14);
		mAnimator->CreateAnimation(L"CoupleMushRightDead", image, math::Vector2(510.0f, 170.0f), math::Vector2(170.0f, 170.0f)
			, math::Vector2(510.0f, 170.0f), 5);

		mTransform->SetMoveDir(enums::eMoveDir::Right);
		mCollider->SetSize(math::Vector2(100.0f, 70.0f));
		mCollider->SetOffset(math::Vector2(4.0f, 4.0f));
		mAnimator->SetAffectedCamera(true);

		mAnimator->PlayAnimation(L"CoupleMushRightDead", true);
		mMonsterState = eMonsterState::Idle;


	}
	void CoupleMush::Update()
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

	void CoupleMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void CoupleMush::Idle()
	{
		mIdleDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mIdleDelay >= 1.8f)
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
				mAnimator->PlayAnimation(L"CoupleMushLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"CoupleMushRightIdle", true);
			}
		}
	}

	void CoupleMush::Move()
	{
		mMoveDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mMoveDelay >= 3.0f)
		{
			mMonsterState = eMonsterState::Idle;
			mMoveDelay = 0.0f;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"CoupleMushLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"CoupleMushRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void CoupleMush::Attack()
	{
	}

	void CoupleMush::Chase()
	{
	}

	void CoupleMush::Hit()
	{
		mMonsterState = eMonsterState::Dead;
	}

	void CoupleMush::Dead()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"CoupleMushRightDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"CoupleMushLeftDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}
	}
	void CoupleMush::OnCollisionEnter(Collider* _other)
	{
	}

	void CoupleMush::OnCollisionStay(Collider* _other)
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
	}

	void CoupleMush::OnCollisionExit(Collider* _other)
	{
	}

}
