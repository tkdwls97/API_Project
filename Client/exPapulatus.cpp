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
		animator->CreateAnimationFolder(L"PapulatusIdle",
			L"..\\Resources\\Maple\\Image\\Monster\\Boss\\Papulatus\\Idle");

		animator->PlayAnimation(L"PapulatusIdle", true);
	}

	void Papulatus::Update()
	{
		GameObject::Update();
	}

	void Papulatus::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

}