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
#include "exDamageManager.h"
#include "exMonsters.h"

namespace ex
{
	PlayerAttack::PlayerAttack(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAttackInfo.AttackCount = 1;
		mAttackInfo.DamagePercentage = 9;
		SetEffectInfo(mAttackInfo);

		Animator* animator = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		math::Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(pos);
		Collider* collider = AddComponent<Collider>();

		enums::eMoveDir dir = GetOwner()->GetComponent<Transform>()->GetMoveDir();
		collider->SetSize(math::Vector2(65.0f, 80.0f));
		//collider->SetSize(math::Vector2(300.0f, 220.0f));

		// 평타 Collider 색 세팅
		collider->SetNomalCollor(RGB(255, 255, 0));
	}

	PlayerAttack::~PlayerAttack()
	{
	}

	void PlayerAttack::Initialize()
	{
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
		Animator* at = SceneManager::GetPlayer()->GetComponent<Animator>();

		eState playerState = SceneManager::GetPlayer()->GetState();
		bool bCheck = at->IsActiveAnimationComplete();
		if (playerState == eState::Attack || playerState == eState::JumpAttack)
		{
			// 충돌 이벤트구현
		}
		else
		{
			// 어택이 끝나면 초기화해줌
			mAttackList.clear();
		}

		tr->SetPosition(pos);
		GameObject::Update();

	}

	void PlayerAttack::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void PlayerAttack::OnCollisionEnter(Collider* _other)
	{
		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (monsters != nullptr)
		{
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				damage->SetPosition(math::Vector2(monsters->GetPositionX(), monsters->GetPositionY() - 50.0f * i));
				damage->PlayDamageAnimation(this->GetEffectInfo().DamagePercentage);
			}
		}
	}

	void PlayerAttack::OnCollisionStay(Collider* _other)
	{
	}

	void PlayerAttack::OnCollisionExit(Collider* _other)
	{
	}
}
