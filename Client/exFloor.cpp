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
		float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
		float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* tr = player->GetComponent<Transform>();
		Rigidbody* rb = player->GetComponent<Rigidbody>();

		if (len < scale)
		{
			math::Vector2 playerPos = tr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;
			tr->SetPosition(playerPos);

		}
	}

	void Floor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		//float len = fabs(other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
		//float scale = fabs(other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);
		//float result = fabs(len - scale);
		//if (result > 1)
		//{
		//	other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
		//}
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
		player->SetState(eState::Fall);
		
	}

}