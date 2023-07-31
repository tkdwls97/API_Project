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
	{
	}

	GreenMush::~GreenMush()
	{
	}

	void GreenMush::Initialize()
	{
		Texture* image = ResourceManager::Load<Texture>(L"GreenMushLeft"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_LEFT.bmp");

		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(L"GreenMushLeftIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			,math::Vector2(60.0f, 60.0f), 1);
		animator->CreateAnimation(L"GreenMushLeftMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		image = ResourceManager::Load<Texture>(L"GreenMushRight"
			, L"..\\Resources\\Maple\\Image\\Monster\\Nomal\\GreenMush_RIGHT.bmp");
		animator->CreateAnimation(L"GreenMushRightIdle", image, math::Vector2(0.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 1);
		animator->CreateAnimation(L"GreenMushRightMove", image, math::Vector2(60.0f, 60.0f), math::Vector2(60.0f, 60.0f)
			, math::Vector2(60.0f, 60.0f), 4);

		animator->PlayAnimation(L"GreenMushLeftIdle", true);

		GetTransform()->SetMoveDir(enums::eMoveDir::Left);
	}

	void GreenMush::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();


		static float MoveDelay = 0.0f;
		static float IdleDelay = 0.0f;

		MoveDelay += Time::GetDeltaTime();

		mDirection = tr->GetMoveDir();
		if (MoveDelay >= 4.0f)
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


		if (mDirection == enums::eMoveDir::Left)
		{
			tr->SetMoveDir(enums::eMoveDir::Left);
			anim->PlayAnimation(L"GreenMushLeftMove", true);
			pos.x -= 50.0f * Time::GetDeltaTime();
		}

		else if (mDirection == enums::eMoveDir::Right)
		{
			tr->SetMoveDir(enums::eMoveDir::Right);
			anim->PlayAnimation(L"GreenMushRightMove", true);
			pos.x += 50.0f * Time::GetDeltaTime();
		}

		IdleDelay += Time::GetDeltaTime();
		if (IdleDelay >= 2.0f)
		{
			if (mDirection == enums::eMoveDir::Left)
			{
				anim->PlayAnimation(L"GreenMushLeftIdle", true);
			}
			else if (mDirection == enums::eMoveDir::Right)
			{
				anim->PlayAnimation(L"GreenMushRightIdle", true);
			}
			IdleDelay = 0.0f;

		}
		
		tr->SetPosition(pos);
	}

	void GreenMush::Render(HDC _hdc)
	{

		GameObject::Render(_hdc);
	}

}