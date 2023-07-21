#include "exMonsters.h"

namespace ex
{
	Monsters::Monsters()
		: mDirection(enums::eMoveDir::End)
	{
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