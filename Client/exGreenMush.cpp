#include "exGreenMush.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exCollider.h"
#include "exPlayerAttack.h"
#include "exPlayer.h"
#include "exSceneManager.h"

namespace ex
{
	GreenMush::GreenMush()
		: mIdleDelay(0.0f)
		, mMoveDelay(0.0f)
	{
	}

	GreenMush::~GreenMush()
	{
	}

	void GreenMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"GreenMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_LEFT.bmp");

		mAnimator->CreateAnimation(L"GreenMushLeftIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushLeftMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushLeftHit", image, math::Vector2(0.0f, 120.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushLeftDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		image = ResourceManager::Load<Texture>(L"GreenMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_RIGHT.bmp");
		mAnimator->CreateAnimation(L"GreenMushRightIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushRightMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushRightHit", image, math::Vector2(0.0f, 120.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushRightDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		mCollider->SetSize(math::Vector2(55.0f, 70.0f));
		mCollider->SetOffset(math::Vector2(5.0f, 4.0f));
		mAnimator->SetAffectedCamera(true);

		mTransform->SetMoveDir(enums::eMoveDir::Left);
		mAnimator->PlayAnimation(L"GreenMushLeftIdle", true);
		mMonsterState = eMonsterState::Idle;
	}

	void GreenMush::Update()
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

	void GreenMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void GreenMush::Idle()
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
				mAnimator->PlayAnimation(L"GreenMushLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"GreenMushRightIdle", true);
			}
		}
	}

	void GreenMush::Move()
	{
		mMoveDelay += Time::GetDeltaTime();

		math::Vector2 pos = mTransform->GetPosition();
		if (mMoveDelay >= 4.0f)
		{
			mMonsterState = eMonsterState::Idle;
			mMoveDelay = 0.0f;
		}
		else
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"GreenMushLeftMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"GreenMushRightMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void GreenMush::Attack()
	{
	}

	void GreenMush::Chase()
	{
	}

	void GreenMush::Hit()
	{
		mMonsterState = eMonsterState::Dead;
	}

	void GreenMush::Dead()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"GreenMushRightDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"GreenMushLeftDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}
	}
	void GreenMush::OnCollisionEnter(Collider* _other)
	{
	}

	void GreenMush::OnCollisionStay(Collider* _other)
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

	void GreenMush::OnCollisionExit(Collider* _other)
	{
	}
}