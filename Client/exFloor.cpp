#include "exFloor.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"
#include "exMonsters.h"
#include "exPlayerFloor.h"
#include "exSceneManager.h"

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

	void Floor::OnCollisionEnter(Collider* _other)
	{
		PlayerFloor* playerFloor = dynamic_cast<PlayerFloor*>(_other->GetOwner());
		if (playerFloor != nullptr)
		{
			Player* player = SceneManager::GetPlayer();

			_other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);
			Transform* playerTr = player->GetComponent<Transform>();
			Rigidbody* playerRb = player->GetComponent<Rigidbody>();
			Rigidbody* rb = playerFloor->GetComponent<Rigidbody>();

			float len = fabs(_other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y);
			float scale = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f);

			if (len < scale)
			{
				math::Vector2 playerPos = player->GetPosition();
				playerPos.y -= (scale - len) - 1.5f;
				playerTr->SetPosition(playerPos);
			}
			math::Vector2 velocityY = playerRb->GetVelocity();
			rb->SetGround(true);

		}

		Monsters* monster = dynamic_cast<Monsters*>(_other->GetOwner());

		if (monster != nullptr)
		{
			Transform* tr = monster->GetComponent<Transform>();
			Rigidbody* rb = monster->GetComponent<Rigidbody>();

			float len = fabs(_other->GetPosition().y - this->GetComponent<Collider>()->GetPosition().y) - 2.0f;
			float scale = fabs(_other->GetSize().y / 2.0f + this->GetComponent<Collider>()->GetSize().y / 2.0f) - 2.0f;

			if (len < scale)
			{
				math::Vector2 monsterPos = tr->GetPosition();
				monsterPos.y -= (scale - len) - 1.5f;
				tr->SetPosition(monsterPos);
			}
			math::Vector2 velocityY = rb->GetVelocity();
			rb->SetGround(true);
		}


	}

	void Floor::OnCollisionStay(Collider* _other)
	{
	}
	void Floor::OnCollisionExit(Collider* _other)
	{
		PlayerFloor* playerFloor = dynamic_cast<PlayerFloor*>(_other->GetOwner());
		Player* player = SceneManager::GetPlayer();
		if (playerFloor != nullptr)
		{
       		playerFloor->GetComponent<Rigidbody>()->SetGround(false);
			if (player->GetState() != eState::Rope)
			{
				player->SetState(eState::Fall);
			}

		}
	}

}