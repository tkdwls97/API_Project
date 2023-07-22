#include "exPlayer.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exGameEffect.h"
#include "exObject.h"

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
		enums::eMoveDir playerType = GetTransform()->GetMoveDir();

		if (playerType == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
			mState = eState::Idle;
		}
		else
		{
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);
			mState = eState::Idle;
		}

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
			GetTransform()->SetMoveDir(enums::eMoveDir::Up);
			mState = eState::Move;
		}
		if (Input::GetKeyDown(eKeyCode::Down))
		{
			if (GetTransform()->GetMoveDir() == enums::eMoveDir::Right)
			{
				mAnimator->PlayAnimation(L"PlayerRightDown", true);
				GetTransform()->SetMoveDir(enums::eMoveDir::Right);
				mState = eState::Move;
			}
			else
			{
				mAnimator->PlayAnimation(L"PlayerLeftDown", true);
				GetTransform()->SetMoveDir(enums::eMoveDir::Left);
				mState = eState::Move;
			}

		}


	}
	void Player::Move()
	{
		mAnimator = AddComponent<Animator>();
		math::Vector2 pos = GetTransform()->GetPosition();

		// 상하좌우 키 입력
		if (Input::GetKeyPressed(eKeyCode::Up))
		{
			//pos.y -= 200.0f * Time::GetDeltaTime();
		}
		else if (Input::GetKeyPressed(eKeyCode::Left))
		{
			pos.x -= 200.0f * Time::GetDeltaTime();
		}
		else if (Input::GetKeyPressed(eKeyCode::Down))
		{
			//pos.y += 200.0f * Time::GetDeltaTime();
		}
		else if (Input::GetKeyPressed(eKeyCode::Right))
		{
			pos.x += 200.0f * Time::GetDeltaTime();
		}

		// 동시 키 입력
		if (Input::GetKeyPressed(eKeyCode::Right) && Input::GetKeyDown(eKeyCode::Left))
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"PlayerRightIdle", true);

		}
		if (Input::GetKeyPressed(eKeyCode::Left) && Input::GetKeyDown(eKeyCode::Right))
		{
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"PlayerLeftIdle", true);
		}
		if (Input::GetKeyDown(eKeyCode::Down) && Input::GetKeyPressed(eKeyCode::Left))
		{
			mState = eState::Down;
			mAnimator->PlayAnimation(L"PlayerLeftMove", true);
		}




		// 키 안누른 상태
		if (Input::GetKeyUp(eKeyCode::Up)
			|| Input::GetKeyUp(eKeyCode::Left)
			|| Input::GetKeyUp(eKeyCode::Down)
			|| Input::GetKeyUp(eKeyCode::Right))
		{
			mAnimator = AddComponent<Animator>();
			if (GetTransform()->GetMoveDir() == enums::eMoveDir::Left)
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
	}
	void Player::Jump()
	{
	}
	void Player::Death()
	{
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