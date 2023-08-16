#include "exDamageSkin.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"


namespace ex
{
	DamageSkin::DamageSkin()
	{
	}

	DamageSkin::~DamageSkin()
	{
	}

	void DamageSkin::Initialize()
	{
	}

	void DamageSkin::Update()
	{
		GameObject::Update();
	}

	void DamageSkin::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void DamageSkin::OnCollisionEnter(Collider* _other)
	{
	}

	void DamageSkin::OnCollisionStay(Collider* _other)
	{
	}

	void DamageSkin::OnCollisionExit(Collider* _other)
	{
	}
}
