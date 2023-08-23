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


// MonsterSkill
#include "exPapulatusSkill1.h"
#include "exPapulatusSkill2.h"
#include "exPapulatusSkill3.h"
#include "exPapulatusSkill4.h"

namespace ex
{
	Papulatus::Papulatus()
		: mbPapulatusHit(false)
		, mAttackDelay(0.0f)
		, mbChaseOn(false)
		, mSkillDelay(1.5f)
		, mUsingSkillNumber(0)
	{
		mMonstersInfo.mMaxHp = 700000000;
		mMonstersInfo.mHp = 700000000;
		mMonstersInfo.mLevel = 190;
		mMonstersInfo.mDamage = 750;
		mSkill1Damage = 411;
		mSkill2Damage = 403;
		mSkill3Damage = 380;
		mSkill4Damage = 0;
	}

	Papulatus::~Papulatus()
	{
	}

	void Papulatus::Initialize()
	{
		// Left
		mAnimator->CreateAnimationFolder(L"PapulatusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Left", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusLeftDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Left", math::Vector2(0.0f, -100.0f));

		// Left Skill
		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Left", math::Vector2(0.0f, -150.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Left", math::Vector2(0.0f, -130.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Left", math::Vector2(0.0f, -140.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusLeftSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Left", math::Vector2(0.0f, -120.0f), 0.077f);

		// Right
		mAnimator->CreateAnimationFolder(L"PapulatusRightIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightHit",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Hit\\Right", math::Vector2(0.0f, -100.0f));

		mAnimator->CreateAnimationFolder(L"PapulatusRightDead",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Die\\Right", math::Vector2(0.0f, -100.0f));

		//Right Skill
		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill1\\Right", math::Vector2(0.0f, -150.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill2",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Right", math::Vector2(0.0f, -130.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill3",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill3\\Right", math::Vector2(0.0f, -140.0f), 0.077f);

		mAnimator->CreateAnimationFolder(L"PapulatusRightSkill4",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill4\\Right", math::Vector2(0.0f, -120.0f), 0.077f);


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
		mDirection = mTransform->GetMoveDir();

		switch (mMonsterState)
		{
		case ex::Monsters::eMonsterState::Idle:
			Idle();
			break;
		case ex::Monsters::eMonsterState::Move:
			Move();
			break;
		case ex::Monsters::eMonsterState::Chase:
			Chase();
			break;
		case ex::Monsters::eMonsterState::Hit:
			Hit();
			break;
		case ex::Monsters::eMonsterState::Dead:
			Dead();
		case ex::Monsters::eMonsterState::Skill1:
			Skill1();
			break;
		case ex::Monsters::eMonsterState::Skill2:
			Skill2();
			break;
		case ex::Monsters::eMonsterState::Skill3:
			Skill3();
			break;
		case ex::Monsters::eMonsterState::Skill4:
			Skill4();
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
			if (mbChaseOn)
			{
				mMonsterState = eMonsterState::Chase;
			}
			else
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
			}
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

		mSkillDelay += Time::GetDeltaTime();
		if (mSkillDelay >= 1.8f)
		{
			math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
			float distanceX = fabs(playerPos.x - this->GetPositionX());
			float distanceY = fabs(playerPos.y - this->GetPositionY());

			mUsingSkillNumber = 2;/*rand() % 4 + 1;*/
			mSkillDelay = 0.0f;

			if (distanceX < 400.0f && distanceY < 200.0f)
			{
				float playerPosX = SceneManager::GetPlayer()->GetPositionX();
				float PapulatusPosX = mTransform->GetPositionX();

				if (mUsingSkillNumber == 1)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill1", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill1", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill1* papulatusSkill1 = new PapulatusSkill1(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill1);
					mMonsterState = eMonsterState::Skill1;
				}
				else if (mUsingSkillNumber == 2)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill2", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill2", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill2* papulatusSkill2 = new PapulatusSkill2(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill2);
					mMonsterState = eMonsterState::Skill2;
				}
				else if (mUsingSkillNumber == 3)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill3", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill3", false);
						mDirection = enums::eMoveDir::Right;
					}
					PapulatusSkill3* papulatusSkill3 = new PapulatusSkill3(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill3);
					mMonsterState = eMonsterState::Skill3;
				}
				else if (mUsingSkillNumber == 4)
				{
					if (playerPosX <= PapulatusPosX)
					{
						mAnimator->PlayAnimation(L"PapulatusLeftSkill4", false);
						mDirection = enums::eMoveDir::Left;
					}
					else
					{
						mAnimator->PlayAnimation(L"PapulatusRightSkill4", false);
						mDirection = enums::eMoveDir::Right;
					}

					PapulatusSkill4* papulatusSkill4 = new PapulatusSkill4(this);
					object::ActiveSceneAddGameObject(enums::eLayerType::Effect, papulatusSkill4);
					mMonsterState = eMonsterState::Skill4;
				}
				mTransform->SetMoveDir(mDirection);
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
				mDirection = enums::eMoveDir::Left;
				pos.x -= 50.0f * Time::GetDeltaTime();
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mDirection = enums::eMoveDir::Right;
				pos.x += 50.0f * Time::GetDeltaTime();
			}
		}

		mTransform->SetMoveDir(mDirection);
		mTransform->SetPosition(pos);
	}

	void Papulatus::Chase()
	{
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float papulatusPosX = mTransform->GetPositionX();
		math::Vector2 pos = mTransform->GetPosition();

		if (playerPosX <= papulatusPosX)
		{
			mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
			pos.x -= 60.0f * Time::GetDeltaTime();
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightMove", true);
			pos.x += 60.0f * Time::GetDeltaTime();
			mDirection = enums::eMoveDir::Right;
		}
		math::Vector2 playerPos = SceneManager::GetPlayer()->GetPosition();
		float distanceX = fabs(playerPos.x - this->GetPositionX());
		float distanceY = fabs(playerPos.y - this->GetPositionY());
		if (distanceX < 400.0f && distanceY < 200.0f)
		{
			mMonsterState = eMonsterState::Idle;
		}

		mTransform->SetPosition(pos);
		mTransform->SetMoveDir(mDirection);
	}

	void Papulatus::Hit()
	{
		mbPapulatusHit = true;
		mbChaseOn = true;
		float playerPosX = SceneManager::GetPlayer()->GetPositionX();
		float GateKeeperPosX = mTransform->GetPositionX();
		if (playerPosX <= GateKeeperPosX)
		{
			mAnimator->PlayAnimation(L"PapulatusLeftHit", false);
			mDirection = enums::eMoveDir::Left;
		}
		else
		{
			mAnimator->PlayAnimation(L"PapulatusRightHit", false);
			mDirection = enums::eMoveDir::Right;
		}
		mHitDelay += Time::GetDeltaTime();
		if (mHitDelay >= 1.3f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PapulatusLeftMove", true);
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mAnimator->PlayAnimation(L"PapulatusRightMove", true);
				mDirection = enums::eMoveDir::Right;
			}
			if (mbPapulatusHit)
			{
				mMonsterState = eMonsterState::Chase;
			}
			else
			{
				mMonsterState = eMonsterState::Move;
			}
				
			mHitDelay = 0.0f;
		}
		if (mMonstersInfo.mHp <= 0)
		{
			mMonsterState = eMonsterState::Dead;
		}
		mTransform->SetMoveDir(mDirection);
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
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill2()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill3()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
	}

	void Papulatus::Skill4()
	{
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			mMonsterState = eMonsterState::Idle;
		}
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