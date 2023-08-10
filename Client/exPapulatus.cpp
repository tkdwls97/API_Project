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
#include "exPlayerAttack.h"
#include "exRaisingblow.h"
#include "exRaisingblowHit.h"
#include "exObject.h"

namespace ex
{
	Papulatus::Papulatus()
	{
	}

	Papulatus::~Papulatus()
	{
	}

	void Papulatus::Initialize()
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidbody = GetComponent<Rigidbody>();
		mCollider = GetComponent<Collider>();

		// Left
		mAnimator->CreateAnimationFolder(L"PapulatusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Left");

		mAnimator->CreateAnimationFolder(L"PapulatusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Left");

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Left");

		mAnimator->CreateAnimationFolder(L"PapulatusLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Left");

		// Right
		mAnimator->CreateAnimationFolder(L"PapulatusRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Right");

		mAnimator->CreateAnimationFolder(L"PapulatusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Right");

		mAnimator->CreateAnimationFolder(L"PapulatusRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Right");

		mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
		mTransform->SetMoveDir(enums::eMoveDir::Left);

		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(math::Vector2(250.0f, 250.0f));
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
		//mMonsterState = eMonsterState::Dead;
	}

	void Papulatus::Dead()
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
	void Papulatus::OnCollisionEnter(Collider* _other)
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

	void Papulatus::OnCollisionStay(Collider* _other)
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

	void Papulatus::OnCollisionExit(Collider* _other)
	{
	}

}