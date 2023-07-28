#include "exPlayer.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exGameEffect.h"
#include "exObject.h"
#include "exRigidbody.h"
#include "exCollider.h"
#include "exCollisionManager.h"

namespace ex
{
	Player::Player()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mState(eState::End)
	{


	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();

		Texture* image = ResourceManager::Load<Texture>(L"PlayerLeft"
			, L"..\\Resources\\Maple\\Image\\Player\\Player_Left.bmp");

		mAnimator->CreateAnimation(L"PlayerLeftIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(100.0f, 100.0f), 5);
		mAnimator->CreateAnimation(L"PlayerLeftMove", image, math::Vector2(0.0f, 100.0f), math::Vector2(100.0f, 100.0f), 3);
		mAnimator->CreateAnimation(L"PlayerLeftDown", image, math::Vector2(0.0f, 400.0f), math::Vector2(100.0f, 100.0f), 1);
		mAnimator->CreateAnimation(L"PlayerLeftJump", image, math::Vector2(0.0f, 600.0f), math::Vector2(100.0f, 100.0f), 1);
		mAnimator->CreateAnimation(L"PlayerLeftAttack", image, math::Vector2(0.0f, 300.0f), math::Vector2(100.0f, 100.0f), 4);

		image = ResourceManager::Load<Texture>(L"PlayerRight"
			, L"..\\Resources\\Maple\\Image\\Player\\Player_Right.bmp");
		mAnimator->CreateAnimation(L"PlayerRightIdle", image, math::Vector2(0.0f, 0.0f), math::Vector2(100.0f, 100.0f), 5);
		mAnimator->CreateAnimation(L"PlayerRightMove", image, math::Vector2(0.0f, 100.0f), math::Vector2(100.0f, 100.0f), 3);
		mAnimator->CreateAnimation(L"PlayerRightDown", image, math::Vector2(0.0f, 400.0f), math::Vector2(100.0f, 100.0f), 1);
		mAnimator->CreateAnimation(L"PlayerRightJump", image, math::Vector2(0.0f, 600.0f), math::Vector2(100.0f, 100.0f), 1);
		mAnimator->CreateAnimation(L"PlayerRightAttack", image, math::Vector2(0.0f, 300.0f), math::Vector2(100.0f, 100.0f), 4);

		image = ResourceManager::Load<Texture>(L"PlayerRope"
			, L"..\\Resources\\Maple\\Image\\Player\\Player_ROPE.bmp");
		mAnimator->CreateAnimation(L"PlayerRopeMove", image, math::Vector2(0.0f, 0.0f), math::Vector2(100.0f, 100.0f), 2);

		
		mCollider->SetSize(math::Vector2(45.0f, 60.0f));
		mCollider->SetOffset(math::Vector2(5.0f, 3.0f));
		mTransform->SetMoveDir(enums::eMoveDir::Right);
		mAnimator->PlayAnimation(L"PlayerRightIdle", true);
		mState = eState::Idle;

	}

	void Player::Update()
	{
		GameObject::Update();
		

		if (mState == eState::Jump)
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

		// 좌우 Idle 상태
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			mState = eState::Idle;
		}
		else if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			mState = eState::Idle;
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
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;

			// Portal 이거나 Rope거나
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", true);
				mState = eState::Down;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", true);
				mState = eState::Down;
			}

		}

		// 점프키
		if (Input::GetKeyDown(eKeyCode::Jump) || Input::GetKeyPressed(eKeyCode::Jump))
		{
			math::Vector2 velocity = mRigidbody->GetVelocity();
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


			if (Input::GetKeyPressed(eKeyCode::Down))
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::Fall;
			}
			mRigidbody->SetVelocity(velocity);

		}

		// 기본 공격 키 
		if (Input::GetKeyDown(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", true);
				mState = eState::Attack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", true);
				mState = eState::Attack;
			}
		}


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
			//pos.x -= 200.0f * Time::GetDeltaTime();
			mRigidbody->AddForce(math::Vector2(-500.0f, 0.0f));
			mTransform->SetMoveDir(enums::eMoveDir::Left);
		}
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			//pos.x += 200.0f * Time::GetDeltaTime();
			mRigidbody->AddForce(math::Vector2(500.0f, 0.0f));
			mTransform->SetMoveDir(enums::eMoveDir::Right);
		}

		// 이동중 공격 상태
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", true);
			mState = eState::Attack;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", true);
			mState = eState::Attack;
		}

		// 좌우 이동중 점프
		if ((Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = 220.0f;
			velocity.y = -1200.0f;
			mState = eState::Jump;
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}
		else if ((Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump)) ||
			(Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyPressed(eKeyCode::Jump)))
		{
			mRigidbody->SetGround(false);
			velocity.x = -220.0f;
			velocity.y = -1200.0f;
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

		if (Input::GetKeyDown(eKeyCode::Left) || (Input::GetKeyPressed(eKeyCode::Left)))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right) || (Input::GetKeyPressed(eKeyCode::Right)))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
		}


		mRigidbody->SetVelocity(velocity);
		mTransform->SetPosition(pos);

	}

	void Player::Down()
	{
		mTransform = GetComponent<Transform>();
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		mRigidbody = GetComponent<Rigidbody>();
		math::Vector2 velocity = mRigidbody->GetVelocity();


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
			//mRigidbody->SetGround(false);
			velocity.y = 700.0f;

		}

		////if(만약 로프에 충돌한다면)
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			mTransform->SetMoveDir(enums::eMoveDir::Down);
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}


		// 밑에 키 Up상태면 다시 Idle상태로 돌아오게 만듬
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator = GetComponent<Animator>();
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

		mTransform->SetPosition(pos);
	}

	void Player::Rope()
	{
		mTransform = GetComponent<Transform>();
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();


		//if (만약 로프에 충돌한다면?)
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			pos.y -= 200.0f * Time::GetDeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::Down))
		{
			pos.y += 200.0f * Time::GetDeltaTime();
		}


		// 윗 방향키 때면 다시 Idle상태로 전환
		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator = GetComponent<Animator>();
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
		GetTransform()->SetPosition(pos);
	}

	void Player::Attack()
	{
		enums::eMoveDir playerDir = mTransform->GetMoveDir();

		// 컨트롤 누를시 좌우 상태에따라 공격 
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", true);
			mRigidbody->SetFriction(500.0f);
			mState = eState::Attack;
		}
		else
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", true);
			mRigidbody->SetFriction(500.0f);
			mState = eState::Attack;
		}

		// 이동중 공격
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerRightAttack", true);

			mState = eState::Attack;
		}

		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator->PlayAnimation(L"PlayerLeftAttack", true);
			mState = eState::Attack;
		}



		if (Input::GetKeyUp(eKeyCode::Ctrl))
		{
			mAnimator = GetComponent<Animator>();
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
	}

	void Player::Jump()
	{
		mTransform = GetComponent<Transform>();
		math::Vector2 pos = mTransform->GetPosition();
		enums::eMoveDir playerDir = mTransform->GetMoveDir();
		math::Vector2 velocity = mRigidbody->GetVelocity();
		mAnimator = GetComponent<Animator>();

		// 좌우 이동중 점프
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);

		}
		if (playerDir == enums::eMoveDir::Right)
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
		}

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
		if (Input::GetKeyPressed(eKeyCode::Jump) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftAttack", true);
				mState = eState::Attack;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightAttack", true);
				mState = eState::Attack;
			}
		}


		if (velocity.y >= 0)
		{
			mState = eState::Fall;

		}

		mTransform->SetPosition(pos);
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

		if (mRigidbody->GetGround() == true)
		{
			if (Input::GetKeyPressed(eKeyCode::Left))
			{
				mAnimator->PlayAnimation(L"PlayerLeftMove", true);
				velocity.x = 0.0f;
				mState = eState::Move;
			}
			else if (Input::GetKeyPressed(eKeyCode::Right))
			{
				mAnimator->PlayAnimation(L"PlayerLeftMove", true);
				velocity.x = 0.0f;
				mState = eState::Move;
			}

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
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}

}
