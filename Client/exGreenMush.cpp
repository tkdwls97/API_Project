#include "exGreenMush.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"


namespace ex
{

	GreenMush::GreenMush()
		: mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mCollider(nullptr)
		, mMonsterState(eMonsterState::Idle)
	{
	}

	GreenMush::~GreenMush()
	{
	}

	void GreenMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"GreenMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_LEFT.bmp");

		mAnimator = AddComponent<Animator>();
		

		mAnimator->CreateAnimation(L"GreenMushLeftIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushLeftMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushLeftDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		image = ResourceManager::Load<Texture>(L"GreenMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_RIGHT.bmp");
		mAnimator->CreateAnimation(L"GreenMushRightIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		mAnimator->CreateAnimation(L"GreenMushRightMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);
		mAnimator->CreateAnimation(L"GreenMushRightDead", image, math::Vector2(0.0f, 0.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		mAnimator->PlayAnimation(L"GreenMushLeftIdle", true);

		GetTransform()->SetMoveDir(enums::eMoveDir::Left);
	}

	void GreenMush::Update()
	{
		GameObject::Update();

		mTransform = GetComponent<Transform>();
		math::Vector2 pos = mTransform->GetPosition();


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


		static float MoveDelay = 0.0f;

		MoveDelay += Time::GetDeltaTime();

		mDirection = mTransform->GetMoveDir();
		if (MoveDelay >= 3.0f)
		{
			if (mDirection == enums::eMoveDir::Right)
			{
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mDirection = enums::eMoveDir::Right;
			}
			MoveDelay = 0.0f;
		}


	
		mTransform->SetPosition(pos);
	}

	void GreenMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

	void GreenMush::OnCollisionEnter(Collider* other)
	{
	}

	void GreenMush::OnCollisionStay(Collider* other)
	{
	}

	void GreenMush::OnCollisionExit(Collider* other)
	{
	}

	void GreenMush::Idle()
	{
	}

	void GreenMush::Move()
	{
	}

	void GreenMush::Attack()
	{
	}

	void GreenMush::Chase()
	{
	}

	void GreenMush::Hit()
	{
	}

	void GreenMush::Dead()
	{
	}

}