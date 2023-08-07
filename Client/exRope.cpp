#include "exRope.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"
#include "exInput.h"
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

	void Rope::OnCollisionEnter(Collider* _other)
	{
	}

	void Rope::OnCollisionStay(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (Input::GetKeyPressed(eKeyCode::Up) || Input::GetKeyPressed(eKeyCode::Down))
		{
			player->SetRopeState(true);
		}
		
	}
	void Rope::OnCollisionExit(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());

		_other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

		player->SetRopeState(false);
		if (player->GetState() == eState::Rope)
		{
			player->SetState(eState::Idle);
		}
	}

}