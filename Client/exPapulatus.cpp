#include "exPapulatus.h"
#include "exTransform.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTexture.h"

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
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimationFolder(L"PapulatusLeftIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle\\Left");

		animator->CreateAnimationFolder(L"PapulatusLeftMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Left");

		animator->CreateAnimationFolder(L"PapulatusLeftSkill1",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Skill2\\Left");

		animator->CreateAnimationFolder(L"PapulatusRightMove",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Move\\Right");

		animator->PlayAnimation(L"PapulatusLeftMove", true);
		GetTransform()->SetMoveDir(enums::eMoveDir::Left);
	}

	void Papulatus::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();


		static float PMoveDelay = 0.0f;
		

		PMoveDelay += Time::GetDeltaTime();

		mDirection = tr->GetMoveDir();
		if (PMoveDelay >= 4.0f)
		{
			if (mDirection == enums::eMoveDir::Right)
			{
				mDirection = enums::eMoveDir::Left;
			}
			else
			{
				mDirection = enums::eMoveDir::Right;
			}
			PMoveDelay = 0.0f;
		}


		if (mDirection == enums::eMoveDir::Left)
		{
			tr->SetMoveDir(enums::eMoveDir::Left);
			anim->PlayAnimation(L"PapulatusLeftMove", true);
			pos.x -= 30.0f * Time::GetDeltaTime();
		}

		else if (mDirection == enums::eMoveDir::Right)
		{
			tr->SetMoveDir(enums::eMoveDir::Right);
			anim->PlayAnimation(L"PapulatusRightMove", true);
			pos.x += 30.0f * Time::GetDeltaTime();
		}
		tr->SetPosition(pos);
	}

	void Papulatus::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Papulatus::OnCollisionEnter(Collider* other)
	{
	}

	void Papulatus::OnCollisionStay(Collider* other)
	{
	}

	void Papulatus::OnCollisionExit(Collider* other)
	{
	}

}