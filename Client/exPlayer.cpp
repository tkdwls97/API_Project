#include "exPlayer.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exObject.h"
#include "exRigidbody.h"
#include "exCollider.h"
#include "exCollisionManager.h"
#include "exPortal.h"


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

		// 왼쪽 애니메이션
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

		// 오른쪽 애니메이션
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


		// 로프 애니메이션
		image = ResourceManager::Load<Texture>(L"PlayerRopeMove"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Rope.bmp");
		mAnimator->CreateAnimation(L"PlayerRopeMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(224.0f, 156.0f)
			, math::Vector2(224.0f, 156.0f), 2, math::Vector2(-23.0f, 0.0f));

		mTransform->SetMoveDir(enums::eMoveDir::Right);
		mCollider->SetSize(math::Vector2(45.0f, 80.0f));
		mCollider->SetOffset(math::Vector2(-12.0f, 10.0f));
		mState = eState::Idle;

	}

	void Player::Update()
	{
		GameObject::Update();

		if (mState == eState::Hit || mhitDelay > 0.0f)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, false);
			mhitDelay += Time::GetDeltaTime();
			if (mhitDelay >= 2.0f)
			{
				CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Monster, true);
				mbInvincible = false;
				mhitDelay = 0.0f;

			}

		}

		if (mState == eState::Jump || mState == eState::Rope)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, false);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
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
		case Player::eState::Skill:
			Skill();
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

		// 좌우 Idle 상태
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
		}

		// Rope, Down, Right, Left 키 입력 이동 상태
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
		if (Input::GetKeyDown(eKeyCode::Up) && mbRopeState) // 로프와 충돌 했다면
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
				mState = eState::Rope;
			}

			mTransform->SetPosition(pos);
			mRigidbody->SetVelocity(velocity);
		}


		// Idle상태일때 점프키 입력
		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{

			mRigidbody->SetGround(false);
			velocity.y = -800.0f;
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

		// 기본 공격 키 
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

		// Idle 중 피격
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


		//mRigidbody->SetVelocity(velocity);

	}

	void Player::Move()
	{
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();

		// 상하좌우 키 입력
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
		}
		if (Input::GetKeyPressed(eKeyCode::Down))
		{
		}
		if (Input::GetKeyPressed(eKeyCode::Left))
		{
			mRigidbody->AddForce(math::Vector2(-500.0f, 0.0f));
			mTransform->SetMoveDir(enums::eMoveDir::Left);
		}
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			mRigidbody->AddForce(math::Vector2(500.0f, 0.0f));
			mTransform->SetMoveDir(enums::eMoveDir::Right);
		}

		// 이동중 공격 상태
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", false);
			//velocity.x = 0.0f;
			mRigidbody->SetVelocity(0.0f);
			mRigidbody->SetFriction(1000.0f);
			mState = eState::Attack;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
			//velocity.x = 0.0f;
			mRigidbody->SetVelocity(0.0f);
			mRigidbody->SetFriction(1000.0f);
			mState = eState::Attack;
		}

		// 좌우 이동중 점프
		if ((Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = 220.0f;
			velocity.y = -1100.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}
		else if ((Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = -220.0f;
			velocity.y = -700.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
		}

		// 좌우 키 입력 중 반대 방향 키 입력 시 Idle상태로 전환
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

		// 키 안누른 상태
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

		// Move 중 피격 상태
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


		// 밑에 누르고 좌우 이동키 누르면 방향에 따라 move
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


		// 밑에 키 Up상태면 다시 Idle상태로 돌아오게 만듬
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
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			velocity.x = -300.0f;
			velocity.y = -150.0f;
			mRigidbody->SetGround(false);
			mState = eState::Jump;
		}
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			velocity.x = 300.0f;
			velocity.y = -150.0f;
			mState = eState::Jump;
			mRigidbody->SetGround(false);
		}
		//mRigidbody->SetGravity(math::Vector2(0.0f, 0.0f));
		mTransform->SetPosition(pos);
		mRigidbody->SetVelocity(velocity);
	}

	void Player::Attack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// 이동중 공격
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

		// 방향에 따라 점프
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
		}
		if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}

		// 점프중 좌우 움직이게 
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

		// 점프 + 공격
		if (Input::GetKeyDown(eKeyCode::Ctrl) || Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", false);
				mState = eState::Attack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", false);
				mState = eState::Attack;
			}
		}

		// 포물선에서 내려오는 상태면 떨어지는상태로 변경해준다
		if (velocity.y >= 0)
		{
			mState = eState::Fall;
		}

		mRigidbody->SetVelocity(velocity);
	}

	void Player::Hit()
	{
		math::Vector2 velocity = mRigidbody->GetVelocity();

		enums::eMoveDir playerDir = mTransform->GetMoveDir();

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
		else if (Input::GetKeyDown(eKeyCode::Right) || Input::GetKeyPressed(eKeyCode::Right))
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


	void Player::Skill()
	{
	}

	void Player::Fall()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		bool bGround = mRigidbody->GetGround();

		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}


		// fall상태 중 좌우 방향키 입력
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

		// 땅에 닿은 상태
		if (bGround)
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
