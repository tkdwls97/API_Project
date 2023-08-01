#include "exEffectManger.h"
#include "exAnimator.h"
#include "exCollider.h"

namespace ex
{

	EffectManger::EffectManger(GameObject* _owner)
		: mOwner(_owner)
	{
		AddComponent<Animator>();
	}

	EffectManger::~EffectManger()
	{
	}

	void EffectManger::Initialize()
	{
	}

	void EffectManger::Update()
	{
	}

	void EffectManger::Render(HDC _hdc)
	{
	}

	void EffectManger::OnCollisionEnter(Collider* other)
	{
	}

	void EffectManger::OnCollisionStay(Collider* other)
	{
	}

	void EffectManger::OnCollisionExit(Collider* other)
	{
	}

}