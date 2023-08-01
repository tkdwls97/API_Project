#include "exObejctAttack.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"

namespace ex
{
	ObejctAttack::ObejctAttack(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		Texture* Rightimage = ResourceManager::Load<Texture>(L"PlayerRightAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Right\\Bmp\\Player_Right_Attack.bmp");

		Texture* Leftimage = ResourceManager::Load<Texture>(L"PlayerRightAttack"
			, L"..\\Resources\\Maple\\Image\\Player2\\Left\\Bmp\\Player_Left_Attack.bmp");

		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = _owner->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(pos);
		Collider* collider = AddComponent<Collider>();

		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		collider->SetSize(math::Vector2(60.0f, 80.0f));
		if (dir == enums::eMoveDir::Right)
		{
			collider->SetOffset(math::Vector2(40.0f, 0.0f));
		}
		else
		{
			collider->SetOffset(math::Vector2(-70.0f, 0.0f));
		}
		
	}

	ObejctAttack::~ObejctAttack()
	{
	}

	void ObejctAttack::Initialize()
	{
	}

	void ObejctAttack::Update()
	{
		// 애니메이션이 끝나면 삭제
		GameObject::Update();
	}

	void ObejctAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void ObejctAttack::OnCollisionEnter(Collider* other)
	{
	}

	void ObejctAttack::OnCollisionStay(Collider* other)
	{
	}

	void ObejctAttack::OnCollisionExit(Collider* other)
	{
	}

}
