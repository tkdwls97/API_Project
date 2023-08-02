#include "exObejctAttack.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"

namespace ex
{
	ObejctAttack::ObejctAttack(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = _owner->GetComponent<Transform>()->GetPosition();
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
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(pos);

		eState playerState = SceneManager::GetPlayer()->GetState();
		if (playerState == eState::Attack)
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, true);
		}
		else
		{
			CollisionManager::CollisionLayerCheck(enums::eLayerType::Effect, enums::eLayerType::Monster, false);
		}

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
