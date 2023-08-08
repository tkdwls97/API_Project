#include "exMonsters.h"
#include "exTransform.h"
#include "exRigidbody.h"
#include "exCollider.h"
#include "exAnimator.h"
namespace ex
{
	Monsters::Monsters()
		: mMonsterState(eMonsterState::Idle)
		, mIdleDelay(0.0f)
		, mMoveDelay(3.0f)
		, mMoveTime(0.0f)
		, mHitDelay(0.0f)
	{
		mRigidbody = AddComponent<Rigidbody>();
		mCollider = AddComponent<Collider>();
		mAnimator = AddComponent<Animator>();
		mTransform = GetComponent<Transform>();
	}

	Monsters::~Monsters()
	{
	}

	void Monsters::Initialize()
	{
	}

	void Monsters::Update()
	{
		GameObject::Update();
	}

	void Monsters::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}


	void Monsters::OnCollisionEnter(Collider* _other)
	{
	}

	void Monsters::OnCollisionStay(Collider* _other)
	{
	}

	void Monsters::OnCollisionExit(Collider* _other)
	{
	}
}