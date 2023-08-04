#include "exRope.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"

namespace ex
{
	Rope::Rope()
	{
	}

	Rope::~Rope()
	{
	}

	void Rope::Initialize()
	{
		Collider* col = AddComponent<Collider>();
		col->SetNomalCollor(RGB(0, 0, 255));
	}

	void Rope::Update()
	{
		GameObject::Update();
	}

	void Rope::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Rope::OnCollisionEnter(Collider* other)
	{
	}

	void Rope::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		player->SetRopeState(true);
		Rigidbody* rb = player->GetComponent<Rigidbody>();

	}
	void Rope::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		//other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

		player->SetRopeState(false);
		player->SetState(eState::Idle);
	}

}