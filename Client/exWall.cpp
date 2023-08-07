#include "exWall.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"

namespace ex
{
	Wall::Wall()
	{
	}

	Wall::~Wall()
	{
	}

	void Wall::Initialize()
	{
	}

	void Wall::Update()
	{
		GameObject::Update();
	}

	void Wall::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Wall::OnCollisionEnter(Collider* _other)
	{
		_other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();

		float len = fabs(_other->GetPosition().x - this->GetComponent<Collider>()->GetPosition().x);
		float scale = fabs(_other->GetSize().x / 2.0f + this->GetComponent<Collider>()->GetSize().x / 2.0f);

		if (len < scale)
		{
			math::Vector2 playerPos = tr->GetPosition();
			playerPos.x += (scale - len) + 1.5f;
			tr->SetPosition(playerPos);
		}
		math::Vector2 velocityY = rb->GetVelocity();

		rb->SetGround(true);
		rb->SetVelocity(-velocityY);

	}

	void Wall::OnCollisionStay(Collider* _other)
	{
	}
	void Wall::OnCollisionExit(Collider* _other)
	{
	}

}