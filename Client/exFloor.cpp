#include "exFloor.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"

namespace ex
{
	Floor::Floor()
	{
	}

	Floor::~Floor()
	{
	}

	void Floor::Initialize()
	{
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
 		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();

		float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
		float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

		if (len < scale)
		{
			math::Vector2 playerPos = tr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;
			tr->SetPosition(playerPos);

		}
		rb->SetGround(true);
	}

	void Floor::OnCollisionStay(Collider* other)
	{
	}

	void Floor::OnCollisionExit(Collider* other)
	{
	}

}