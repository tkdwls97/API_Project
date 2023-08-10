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
		col->SetNomalCollor(RGB(255, 255, 0));
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
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (player != nullptr && player->GetState() == eState::Rope)
		{
			Rigidbody* rb = player->GetComponent<Rigidbody>();

			rb->SetVelocity(math::Vector2(0.0f, 0.0f));
		}
	}

	void Rope::OnCollisionStay(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		if (Input::GetKeyPressed(eKeyCode::Up) || Input::GetKeyPressed(eKeyCode::Down))
		{
			player->SetRopeState(true);
			// ���� ���¿��� ���� Pos.x�� �÷��̾ ����
			player->SetPositionX(this->GetPositionX() + 13.5f);
		}
		if (player != nullptr && player->GetState() == eState::Rope)
		{

			Rigidbody* rb = player->GetComponent<Rigidbody>();
			rb->SetVelocity(math::Vector2(0.0f, 0.0f));
			rb->SetGround(true);
		}

	}
	void Rope::OnCollisionExit(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());

		if (player->GetState() == eState::Rope)
		{
			player->SetState(eState::Idle);
			Rigidbody* rb = player->GetComponent<Rigidbody>();
			// �������� ������ �ٽ� �߷��� ����ޱ����� SetGround(false)
			rb->SetGround(false);
		}
		player->SetRopeState(false);

	}

}