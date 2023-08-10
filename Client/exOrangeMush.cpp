#include "exOrangeMush.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exAnimator.h"
#include "exInput.h" 
#include "exTime.h"
#include "exObject.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exSceneManager.h"
#include "exPlayerAttack.h"
#include "exPlayer.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"


namespace ex
{
	OrangeMush::OrangeMush()
		: mIdleDelay(0.0f)
		, mMoveDelay(0.0f)
	{
	}

	OrangeMush::~OrangeMush()
	{
	}

	void OrangeMush::Initialize()
	{

		mAnimator->CreateAnimationFolder(L"LeftOrangeMushIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Idle\\Left",math::Vector2(0.0f,0.0f), 0.3f);

		mAnimator->CreateAnimationFolder(L"LeftOrangeMushMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Move\\Left", math::Vector2(0.0f, 0.0f), 0.3f);

		mAnimator->CreateAnimationFolder(L"LeftOrangeMushDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Die\\Left", math::Vector2(0.0f, 0.0f), 0.3f);


		mAnimator->CreateAnimationFolder(L"RightOrangeMushIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Idle\\Right", math::Vector2(0.0f, 0.0f), 0.3f);

		mAnimator->CreateAnimationFolder(L"RightOrangeMushMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Move\\Right", math::Vector2(0.0f, 0.0f), 0.3f);

		mAnimator->CreateAnimationFolder(L"RightOrangeMushDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\OrangeMush\\Die\\Right", math::Vector2(0.0f, 0.0f), 0.3f);

		mCollider->SetSize(math::Vector2(63.0f, 63.0f));
		mCollider->SetOffset(math::Vector2(4.0f, 4.0f));
		mAnimator->SetAffectedCamera(true);
		mDirection = mTransform->GetMoveDir();
		mMoveTime = mMoveDelay;
	}
	void OrangeMush::Update()
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

	void OrangeMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void OrangeMush::Idle()
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
				mAnimator->PlayAnimation(L"LeftOrangeMushIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"RightOrangeMushIdle", true);
			}
		}
	}

	void OrangeMush::Move()
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
				mAnimator->PlayAnimation(L"LeftOrangeMushMove", true);
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"RightOrangeMushMove", true);
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetPosition(pos);
	}

	void OrangeMush::Attack()
	{
	}

	void OrangeMush::Chase()
	{
	}

	void OrangeMush::Hit()
	{
		enums::eMoveDir playerDir = SceneManager::GetPlayer()->GetTransform()->GetMoveDir();
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

	void OrangeMush::Dead()
	{
		if (mDirection == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"LeftOrangeMushDead", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"RightOrangeMushDead", false);

		}

		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			Destroy(this);
		}
	}
	void OrangeMush::OnCollisionEnter(Collider* _other)
	{
	}

	void OrangeMush::OnCollisionStay(Collider* _other)
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

	void OrangeMush::OnCollisionExit(Collider* _other)
	{
	}

}
