#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exPortal.h"
#include "exPlayerFloor.h"
#include "exSceneManager.h"
// Component
#include "exTransform.h"
#include "exRigidbody.h"
#include "exAnimator.h"
#include "exCollider.h"
// Skill
#include "exWarriorLeap.h"
#include "exRaisingblow.h"
#include "exUpperCharge.h"

namespace ex
{
	Player::Player()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mState(eState::End)
		, mhitDelay(0.0f)
		, mbInvincible(false)
		, mbPortalState(false)
		, mbRopeState(false)
		, mbDoubleJump(false)
	{
		mInfo.mHp = 50000;
		mInfo.mMP = 30000;
		mInfo.mLevel = 200;
		mInfo.mSpeed = 300;
		mInfo.mDamage = 10000;
		mInfo.mDef = 1000;
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();
		mTransform = GetComponent<Transform>();

		// ���� �ִϸ��̼�
		Texture* image = ResourceManager::Load<Texture>(L"PlayerLeftIdle"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Idle.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Move.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 4, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftDown"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Down.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftDown", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftJump"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Jump.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftJump", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Hit.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftHit", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f));

		image = ResourceManager::Load<Texture>(L"PlayerLeftAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Attack.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftAttack", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3, math::Vector2(-23.0f, 0.0f), 0.14f);

		// ���� ��ų �ִϸ��̼�

		// png �϶�
		/*image = ResourceManager::Load<Texture>(L"PlayerLeftRaisingBlow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Left\\Player_Left_RaisingBlow.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftRaisingBlow", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 11, math::Vector2(0.0f, 0.0f), 0.1f);*/

		// bmp �϶�
		image = ResourceManager::Load<Texture>(L"PlayerLeftRaisingBlow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Left\\Player_Left_RaisingBlow.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftRaisingBlow", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 11, math::Vector2(0.0f, 0.0f), 0.02f);

		image = ResourceManager::Load<Texture>(L"PlayerLeftUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\UpperCharge\\Left\\Player_Left_UpperCharge.bmp");
		mAnimator->CreateAnimation(L"PlayerLeftUpperCharge", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 9, math::Vector2(0.0f, 0.0f), 0.015f);

		// ������ �ִϸ��̼�
		image = ResourceManager::Load<Texture>(L"PlayerRightIdle"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Idle.bmp");
		mAnimator->CreateAnimation(L"PlayerRightIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3);

		image = ResourceManager::Load<Texture>(L"PlayerRightMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Move.bmp");
		mAnimator->CreateAnimation(L"PlayerRightMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 4);

		image = ResourceManager::Load<Texture>(L"PlayerRightDown"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Down.bmp");
		mAnimator->CreateAnimation(L"PlayerRightDown", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1);

		image = ResourceManager::Load<Texture>(L"PlayerRightJump"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Jump.bmp");
		mAnimator->CreateAnimation(L"PlayerRightJump", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 1);

		image = ResourceManager::Load<Texture>(L"PlayerRightHit"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Hit.bmp");
		mAnimator->CreateAnimation(L"PlayerRightHit", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 3);

		image = ResourceManager::Load<Texture>(L"PlayerRightAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Attack.bmp");
		mAnimator->CreateAnimation(L"PlayerRightAttack", image, math::Vector2(672.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 3, math::Vector2(0.f, 0.f), 0.14f);

		// ������ ��ų �ִϸ��̼�
		// png�϶� 
		//image = ResourceManager::Load<Texture>(L"PlayerRightRaisingBlow"
		//	, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Right\\Player_Right_RaisingBlow.bmp");
		//mAnimator->CreateAnimation(L"PlayerRightRaisingBlow", image, math::Vector2(2464.0f, 0.0f), math::Vector2(224.0f, 156.0f)
		//	, math::Vector2(-224.0f, 0.0f), 11, math::Vector2(0.0f, 0.0f), 0.1f);


		//// bmp�϶� 
		image = ResourceManager::Load<Texture>(L"PlayerRightRaisingBlow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\RaisingBlow\\Right\\Player_Right_RaisingBlow.bmp");
		mAnimator->CreateAnimation(L"PlayerRightRaisingBlow", image, math::Vector2(2464.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 11, math::Vector2(0.0f, 0.0f), 0.02f);

		image = ResourceManager::Load<Texture>(L"PlayerRightUpperCharge"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Skill\\UpperCharge\\Right\\Player_Right_UpperCharge.bmp");
		mAnimator->CreateAnimation(L"PlayerRightUpperCharge", image, math::Vector2(2016.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(-224.0f, 0.0f), 9, math::Vector2(0.0f, 0.0f), 0.15f);

		// ����
		image = ResourceManager::Load<Texture>(L"PlayerRopeMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Rope.bmp");
		mAnimator->CreateAnimation(L"PlayerRopeMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 2, math::Vector2(-23.0f, 0.0f));

		mTransform->SetMoveDir(enums::eMoveDir::Right);
		mCollider->SetSize(math::Vector2(45.0f, 70.0f));
		mCollider->SetOffset(math::Vector2(-12.0f, 10.0f));
		mState = eState::Idle;

	}

	void Player::Update()
	{

		if (mState == eState::Hit || mhitDelay > 0.0f)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, false);
			mhitDelay += Time::GetDeltaTime();
			if (mhitDelay >= 1.0f)
			{
				CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
				mbInvincible = false;
				mhitDelay = 0.0f;

				bool bCheack = mRigidbody->GetGround();
				if (bCheack)
				{
					mState = eState::Idle;
				}
			}
		}

		if (mState == eState::Jump || mState == eState::Rope || mState == eState::DoubleJump ||
			mState == eState::UpperCharge)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::PlayerFloor, enums::eLayerType::Floor, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::PlayerFloor, enums::eLayerType::Floor, true);
		}

		if (mState == eState::Jump || mState == eState::Rope || mState == eState::DoubleJump)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
		}

		// ������ ���������� �浹üũ�� �������� ����
		if (mState == eState::Attack || mState == eState::JumpAttack || mState == eState::RaisingBlow)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, false);
		}

		switch (mState)
		{
		case Player::eState::Idle:
			Idle();
			break;
		case Player::eState::Move:
			Move();
			break;
		case Player::eState::Jump:
			Jump();
			break;
		case Player::eState::DoubleJump:
			DoubleJump();
			break;
		case Player::eState::Down:
			Down();
			break;
		case Player::eState::Fall:
			Fall();
			break;
		case Player::eState::Rope:
			Rope();
			break;
		case Player::eState::Attack:
			Attack();
			break;
		case Player::eState::JumpAttack:
			JumpAttack();
			break;
		case Player::eState::RaisingBlow:
			RaisingBlow();
			break;
		case Player::eState::UpperCharge:
			Uppercharge();
			break;
		case Player::eState::Hit:
			Hit();
			break;
		case Player::eState::Death:
			Death();
			break;
		case Player::eState::End:
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void Player::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Player::Idle()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		math::Vector2 pos = mTransform->GetPosition();

		// �¿� Idle ����
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
		}

		// Rope, Down, Right, Left Ű �Է� �̵� ����
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Up) && mbRopeState) // ������ �浹 �ߴٸ�
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y -= 200.0f * Time::GetDeltaTime();
			mState = eState::Rope;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", true);
				mState = eState::Down;
			}
			else if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", true);
				mState = eState::Down;
			}

			if (mbRopeState)
			{
				mAnimator->PlayAnimation(L"PlayerRopeMove", true);
				pos.y += 200.0f * Time::GetDeltaTime();
				//mState = eState::RopeDown;
				mState = eState::Rope;
			}

			mTransform->SetPosition(pos);
			mRigidbody->SetVelocity(velocity);
		}


		// Idle�����϶� ����Ű �Է�
		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{
			mRigidbody->SetGround(false);
			velocity.y = -700.0f;
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::Jump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Jump;
			}
			mRigidbody->SetVelocity(velocity);
		}

		// �⺻ ���� Ű 
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::Attack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::Attack;
			}

		}

		// ����¡ ��ο�
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			}
			mState = eState::RaisingBlow;
		}

		// ���� ����
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			velocity.y = -1000.0f;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			mState = eState::UpperCharge;
			mRigidbody->SetVelocity(velocity);
		}

		// Idle �� �ǰ�
		bool bCheck = mCollider->GetCollisionType();
		if (bCheck && !mbInvincible)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftHit", true);
			}
			else if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightHit", true);
			}
			mState = eState::Hit;
		}

	}

	void Player::Move()
	{
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		if (Input::GetKeyPressed(eKeyCode::Left))
		{
			//mRigidbody->AddForce(math::Vector2(-500.0f, 0.0f));
			velocity.x = -200.0f;
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			//mRigidbody->AddForce(math::Vector2(500.0f, 0.0f));
			velocity.x = 200.0f;
			mTransform->SetMoveDir(enums::eMoveDir::Right);
		}

		// �̵��� ���� ����
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			mRigidbody->SetVelocity(0.0f);
			mState = eState::Attack;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			mRigidbody->SetVelocity(0.0f);
			mState = eState::Attack;
		}

		// ����¡ ��ο�
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			mState = eState::RaisingBlow;
		}
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			mState = eState::RaisingBlow;
		}

		// ���� ����
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			velocity.y = -1000.0f;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			mState = eState::UpperCharge;
			mRigidbody->SetVelocity(velocity);
		}


		// �¿� �̵��� ����
		if ((Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = 220.0f;
			velocity.y = -600.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}
		else if ((Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = -220.0f;
			velocity.y = -600.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
		}

		// �¿� Ű �Է� �� �ݴ� ���� Ű �Է� �� Idle���·� ��ȯ
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			mState = eState::Idle;
			velocity = math::Vector2(0.0f, 0.0f);
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			mState = eState::Idle;
			velocity = math::Vector2(0.0f, 0.0f);
		}

		// Ű �ȴ��� ����
		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Down)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
			mRigidbody->SetFriction(1000.0f);
		}
		else
		{
			mRigidbody->SetFriction(0.0f);
		}

		// Move �� �ǰ� ����
		bool bCheck = mCollider->GetCollisionType();
		if (bCheck && !mbInvincible)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftHit", true);
			}
			else if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightHit", true);
			}
			mState = eState::Hit;
			velocity.x = 0;
		}

		mRigidbody->SetVelocity(velocity);
	}

	void Player::Down()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightDown", true);
		}
		else if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftDown", true);
		}


		// �ؿ� ������ �¿� �̵�Ű ������ ���⿡ ���� move
		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Right))
		{
			mTransform->SetMoveDir(enums::eMoveDir::Right);
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}
		else if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Left))
		{
			mTransform->SetMoveDir(enums::eMoveDir::Left);
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}

		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetGround(false);

			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Fall;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::Fall;
			}

		}


		// �ؿ� Ű Up���¸� �ٽ� Idle���·� ���ƿ��� ����
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mTransform->SetMoveDir(enums::eMoveDir::Left);
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mTransform->SetMoveDir(enums::eMoveDir::Right);
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}

		}
	}

	void Player::Rope()
	{
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		mRigidbody->SetGround(false);

		// ���� ���¿� ���� �������� �ʱ�ȭ
		mbDoubleJump = false;
		if (Input::GetKeyPressed(eKeyCode::Up) || Input::GetKeyDown(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y -= 200.0f * Time::GetDeltaTime();
		}
		else if (Input::GetKeyPressed(eKeyCode::Down) || Input::GetKeyDown(eKeyCode::Down))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			pos.y += 200.0f * Time::GetDeltaTime();
		}


		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetLimitedVeloctyX(700.0f);
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			velocity.x = -300.0f;
			velocity.y = -200.0f;
			mState = eState::Jump;
			mRigidbody->SetVelocity(velocity);
		}
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetLimitedVeloctyX(700.0f);
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			velocity.x = 300.0f;
			velocity.y = -200.0f;
			mState = eState::Jump;
			mRigidbody->SetVelocity(velocity);
		}
		mTransform->SetPosition(pos);

	}


	void Player::Attack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// �̵��� ����
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", false);
		}

		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
		}

		if (Input::GetKeyPressed(eKeyCode::Jump) || Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			}

		}

		bool IsComplete = mAnimator->IsActiveAnimationComplete();
		if (IsComplete)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
		}
		mRigidbody->SetFriction(1000.0f);
	}

	void Player::Jump()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();


		// ������ �¿� �����̰� 
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);

		}
		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}

		// ���� + ����
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::JumpAttack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::JumpAttack;
			}
		}


		// mbDoubleJump �� false�϶� ������ ������ ��������
		if (false == mbDoubleJump && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetLimitedVeloctyX(700.0f);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				velocity.x = -700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				velocity.x = 700.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			WarriorLeap* warriorLeap = new WarriorLeap(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, warriorLeap);
			mRigidbody->SetVelocity(velocity);
		}


		// ���������� �������� ���¸� �������»��·� �������ش�
		if (velocity.y >= 0 && mState != eState::Rope)
		{
			mState = eState::Fall;
		}


		//mRigidbody->SetVelocity(velocity);
	}

	void Player::JumpAttack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		bool bCheck = mAnimator->IsActiveAnimationComplete();

		if (bCheck)
		{
			mState = eState::Fall;
		}
	}

	void Player::DoubleJump()
	{
		math::Vector2 velocity = mRigidbody->GetVelocity();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// ���� ������ ����߱⶧���� 
		// true�� ����
		mbDoubleJump = true;
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			velocity.y = -1000.0f;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			mState = eState::UpperCharge;
			mRigidbody->SetVelocity(velocity);
		}

		if (velocity.y >= 0 && mState != eState::Rope)
		{
			mState = eState::Fall;
		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}
	}

	void Player::Hit()
	{
		math::Vector2 velocity = mRigidbody->GetVelocity();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		mbDoubleJump = false;

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftHit", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightHit", true);
		}

		if (Input::GetKeyDown(eKeyCode::Left) || Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}

		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			}
			mState = eState::Attack;
		}

		// ����¡ ��ο�
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
		{
			Raisingblow* raisingBlow = new Raisingblow(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
			}
			mState = eState::RaisingBlow;
		}

		// ���� ����
		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidbody->SetGround(false);
			UpperCharge* upperCharge = new UpperCharge(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, upperCharge);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftUpperCharge", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightUpperCharge", false);
			}
			velocity.y = -1000.0f;
			mState = eState::UpperCharge;
			mRigidbody->SetVelocityY(velocity.y);
		}

		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", false);
			}
			mState = eState::Jump;
		}

		if (Input::GetKeyDown(eKeyCode::Down) || Input::GetKeyPressed(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", false);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", false);
			}
			mState = eState::Down;
		}

		velocity.x = 0.0f;
		mbInvincible = true;
		mRigidbody->SetVelocity(velocity);
	}

	void Player::Death()
	{
	}


	void Player::RaisingBlow()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (bCheck)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			}
			mState = eState::Idle;
		}
		bool bGround = mRigidbody->GetGround();
		if (bGround)
		{
			mRigidbody->SetVelocityX(0.0f);
		}
	}

	void Player::Uppercharge()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		// �ִϸ��̼� ����� ��������
		if (bCheck)
		{
			bool bGround = mRigidbody->GetGround();

			if (bGround)
			{
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				}
				mState = eState::Idle;
				mRigidbody->SetVelocityX(0.0f);
			}
			else
			{
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightJump", true);
				}
				mState = eState::Jump;
			}
			if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
			{
				mAnimator->PlayAnimation(L"PlayerRopeMove", true);
				mState = eState::Rope;
			}
		}

		if (velocity.y >= 0 && mState != eState::Rope)
		{
			mState = eState::Fall;
		}

	}

	void Player::Fall()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		// fall���� �� �¿� ����Ű �Է�
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Right);

		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mTransform->SetMoveDir(enums::eMoveDir::Left);

		}

		// mbDoubleJump �� false�϶� ������ ������
		if (false == mbDoubleJump && Input::GetKeyDown(eKeyCode::Jump))
		{
			mRigidbody->SetLimitedVeloctyX(500.0f);
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				velocity.x = -600.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				velocity.x = 600.0f;
				velocity.y = -300.0f;
				mState = eState::DoubleJump;
			}
			WarriorLeap* warriorLeap = new WarriorLeap(this);
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, warriorLeap);
			mRigidbody->SetVelocity(velocity);
		}


		// ���� ���� ����
		bool bGround = mRigidbody->GetGround();
		if (bGround)
		{
			mRigidbody->SetLimitedVeloctyX(200.0f);
			mRigidbody->SetVelocityX(0.0f);
			// ���� ������ �������� �ʱ�ȭ
			mbDoubleJump = false;
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}
		}

		if (mbRopeState && Input::GetKeyPressed(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}

		if (bGround && Input::GetKeyPressed(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}
		else if (bGround && Input::GetKeyPressed(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}

		// ���� + ����
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::JumpAttack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::JumpAttack;
			}
		}

		// ����¡ ��ο�
		if (bGround == false)
		{

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::A))
			{
				Raisingblow* raisingBlow = new Raisingblow(this);
				object::ActiveSceneAddGameObject(enums::eLayerType::Effect, raisingBlow);
				if (playerDir == enums::eMoveDir::Left)
				{
					mAnimator->PlayAnimation(L"PlayerLeftRaisingBlow", false);
				}
				else
				{
					mAnimator->PlayAnimation(L"PlayerRightRaisingBlow", false);
				}
				mState = eState::RaisingBlow;
			}
		}

		if (bGround && mbInvincible)
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftHit", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightHit", true);

			}
			mState = eState::Hit;
			mRigidbody->SetFriction(1000.0f);
		}
	}

	void Player::OnCollisionEnter(Collider* _other)
	{
		enums::eLayerType Type = _other->GetOwner()->GetLayerType();
		if (Type == enums::eLayerType::Monster && mbInvincible == false)
		{
			mCollider->SetCollisionType(true);
			mState = eState::Hit;
		}

	}
	void Player::OnCollisionStay(Collider* _other)
	{

		enums::eLayerType Type = _other->GetOwner()->GetLayerType();
		if (Type == enums::eLayerType::Potal)
		{
			mbPortalState = true;
		}
	}
	void Player::OnCollisionExit(Collider* _other)
	{
		mCollider->SetCollisionType(false);

		Portal* potal = dynamic_cast<Portal*>(_other->GetOwner());
		if (potal != nullptr)
		{
			mbPortalState = false;
		}
	}

}
