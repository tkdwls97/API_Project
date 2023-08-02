#include "exPlayerAttack.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"

namespace ex
{
	PlayerAttack::PlayerAttack(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
	}

	PlayerAttack::~PlayerAttack()
	{
	}

	void PlayerAttack::Initialize()
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(pos);
		Collider* collider = AddComponent<Collider>();

		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		collider->SetSize(math::Vector2(65.0f, 80.0f));

		if (dir == enums::eMoveDir::Right)
		{
			collider->SetOffset(math::Vector2(42.0f, 10.0f));
		}
		else
		{
			collider->SetOffset(math::Vector2(-68.0f, 10.0f));
		}
		collider->SetAttackCollor(RGB(0, 0, 255));
		collider->SetAttackCollisionCollor(RGB(255, 0, 0));
	}

	void PlayerAttack::Update()
	{


		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		Collider* collider = GetComponent<Collider>();

		if (dir == enums::eMoveDir::Right)
		{
			collider->SetOffset(math::Vector2(42.0f, 10.0f));
		}
		else
		{
			collider->SetOffset(math::Vector2(-68.0f, 10.0f));
		}

		tr->SetPosition(pos);

		eState playerState = SceneManager::GetPlayer()->GetState();
		if (playerState == eState::Attack)
		{
			// 충돌 이벤트구현
		}
		else
		{

		}

		GameObject::Update();

	}

	void PlayerAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void PlayerAttack::OnCollisionEnter(Collider* _other)
	{
	}

	void PlayerAttack::OnCollisionStay(Collider* _other)
	{
		eState playerState = SceneManager::GetPlayer()->GetState();

		if (playerState == eState::Attack)
		{
			Destroy(_other->GetOwner());
		}
		else
		{
		}
	}

	void PlayerAttack::OnCollisionExit(Collider* _other)
	{
	}
}
