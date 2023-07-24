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

namespace ex
{
	Player::Player()
		: mAnimator(nullptr)
		, mState(eState::End)
	{


	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		mAnimator = AddComponent<Animator>();

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

		//Transform* tr = AddComponent<Transform>();
		//tr->SetMoveType(eMoveType::Right);
		GetTransform()->SetMoveDir(enums::eMoveDir::Right);
		mAnimator->PlayAnimation(L"PlayerRightIdle", true);
		mState = eState::Idle;
		mRigidbody = AddComponent<Rigidbody>();

	}

	void Player::Update()
	{
		GameObject::Update();

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
		case Player::eState::DownJump:
			DownJump();
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
		mAnimator = GetComponent<Animator>();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();

		// �¿� Idle ����
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

		// Rope, Down, Right, Left Ű �Է� �̵� ����
		if (Input::GetKeyDown(eKeyCode::Right))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			GetTransform()->SetMoveDir(enums::eMoveDir::Right);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Left))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			GetTransform()->SetMoveDir(enums::eMoveDir::Left);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Up))
		{
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;

			// Portal �̰ų� Rope�ų�
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

		// ����Ű
		if (Input::GetKeyDown(eKeyCode::Jump))
		{
			Rigidbody* rb = GetComponent<Rigidbody>();
			math::Vector2 velocity = rb->GetVelocity();
			velocity.y = -500.0f;
			rb->SetVelocity(velocity);
			rb->SetGround(false);
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
				mState = eState::DownJump;
			}
		}

		// �⺻ ���� Ű 
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
		mAnimator = GetComponent<Animator>();
		math::Vector2 pos = GetTransform()->GetPosition();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();
		// �����¿� Ű �Է�
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
		}
		if (Input::GetKeyPressed(eKeyCode::Down))
		{
		}
		if (Input::GetKeyPressed(eKeyCode::Left))
		{
			pos.x -= 200.0f * Time::GetDeltaTime();
			//GetComponent<Rigidbody>()->AddForce(math::Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKeyPressed(eKeyCode::Right))
		{
			pos.x += 200.0f * Time::GetDeltaTime();
			//GetComponent<Rigidbody>()->AddForce(math::Vector2(200.0f, 0.0f));
		}

		// �̵��� ���� ����
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

		// �¿� �̵��� ����
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mState = eState::Jump;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mState = eState::Jump;
		}

		// �¿� Ű �Է� �� �ݴ� ���� Ű �Է� �� Idle���·� ��ȯ
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyPressed(eKeyCode::Left))
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

		// Ű �ȴ��� ����
		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Down)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			mAnimator = AddComponent<Animator>();

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

		if (Input::GetKeyDown(eKeyCode::Left) || (Input::GetKeyPressed(eKeyCode::Left)))
		{
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
		}
		if (Input::GetKeyDown(eKeyCode::Right) || (Input::GetKeyPressed(eKeyCode::Right)))
		{
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
		}


		GetTransform()->SetPosition(pos);

	}

	void Player::Down()
	{
		math::Vector2 pos = GetTransform()->GetPosition();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();
		Rigidbody* rb = GetComponent<Rigidbody>();
		math::Vector2 velocity = rb->GetVelocity();


		// �ؿ� ������ �¿� �̵�Ű ������ ���⿡ ���� move
		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Right))
		{
			GetTransform()->SetMoveDir(enums::eMoveDir::Right);
			mAnimator->PlayAnimation(L"PlayerRightMove", true);
			mState = eState::Move;
		}
		else if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Left))
		{
			GetTransform()->SetMoveDir(enums::eMoveDir::Left);
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
			mState = eState::Move;
		}

		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);
				mState = eState::DownJump;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
				mState = eState::DownJump;
			}
			rb->SetGround(false);
			velocity.y = +500.0f;

		}

		////if(���� ������ �浹�Ѵٸ�)
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			GetTransform()->SetMoveDir(enums::eMoveDir::Down);
			mAnimator->PlayAnimation(L"PlayerRopeMove", true);
			mState = eState::Rope;
		}


		// �ؿ� Ű Up���¸� �ٽ� Idle���·� ���ƿ��� ����
		if (Input::GetKeyUp(eKeyCode::Down))
		{
			mAnimator = AddComponent<Animator>();
			if (playerDir == enums::eMoveDir::Left)
			{
				GetTransform()->SetMoveDir(enums::eMoveDir::Left);
				mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
				mState = eState::Idle;
			}
			else
			{
				GetTransform()->SetMoveDir(enums::eMoveDir::Right);
				mAnimator->PlayAnimation(L"PlayerRightIdle", true);
				mState = eState::Idle;
			}

		}

		GetTransform()->SetPosition(pos);
	}

	void Player::Rope()
	{
		math::Vector2 pos = GetTransform()->GetPosition();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();
		

		//if (���� ������ �浹�Ѵٸ�?)
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			pos.y -= 200.0f * Time::GetDeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::Down))
		{
			pos.y += 200.0f * Time::GetDeltaTime();
		}


		// �� ����Ű ���� �ٽ� Idle���·� ��ȯ
		if (Input::GetKeyUp(eKeyCode::Up))
		{
			mAnimator = AddComponent<Animator>();
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
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();

		// ��Ʈ�� ������ �¿� ���¿����� ���� 
		if (Input::GetKeyPressed(eKeyCode::Ctrl))
		{
			mAnimator = AddComponent<Animator>();
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

			// �̵��� ����
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
		}


		if (Input::GetKeyUp(eKeyCode::Ctrl))
		{
			mAnimator = AddComponent<Animator>();
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
		math::Vector2 pos = GetTransform()->GetPosition();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();
		Rigidbody* rb = GetComponent<Rigidbody>();
		math::Vector2 velocity = rb->GetVelocity();

		if (playerDir == enums::eMoveDir::Left)
		{
			velocity.x = -300.0f;
		}
		else
		{
			velocity.x = 300.0f;
		}
		velocity.y = -500.0f;
		rb->SetVelocity(velocity);
		rb->SetGround(false);

		// �¿� �̵��� ����
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerRightJump", true);
			mState = eState::Jump;
		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Jump))
		{
			mAnimator->PlayAnimation(L"PlayerLeftJump", true);
			mState = eState::Jump;
		}


		// ���� + ����
		if (Input::GetKeyPressed(eKeyCode::Jump) && Input::GetKeyDown(eKeyCode::Ctrl))
		{
			mAnimator = AddComponent<Animator>();
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

		//�� ����Ű ���� �ٽ� Idle���·� ��ȯ
		if (Input::GetKeyUp(eKeyCode::Jump))
		{
			mAnimator = AddComponent<Animator>();
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
	void Player::Death()
	{
	}
	void Player::DownJump()
	{
		math::Vector2 pos = GetTransform()->GetPosition();
		enums::eMoveDir playerDir = GetTransform()->GetMoveDir();
		Rigidbody* rb = GetComponent<Rigidbody>();
		math::Vector2 velocity = rb->GetVelocity();

		if (Input::GetKeyPressed(eKeyCode::Down) && Input::GetKeyDown(eKeyCode::Jump))
		{
			if (playerDir == enums::eMoveDir::Left)
			{
				mAnimator->PlayAnimation(L"PlayerLeftJump", true);

			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerRightJump", true);
			}
			mState = eState::DownJump;
			velocity.x = 0.0f;
			velocity.y = 500.0f;
		}

		if (rb->GetGround())
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


	}
	void Player::Skill()
	{
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
