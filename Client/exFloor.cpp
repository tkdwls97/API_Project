#include "exFloor.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"
#include "exMonsters.h"
#include "exSceneManager.h"
#include "exPapulatus.h"

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
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Rigidbody* rb = obj->GetComponent<Rigidbody>();
		Collider* col = obj->GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// �浹ü�� ��ġ
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// �ٴ� ��ü�� ��ġ
		math::Vector2 objSize = col->GetSize();										// �浹ü�� ������
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// �ٴ� ��ü�� ũ��

		float gap = floorPos.y - objPos.y;						// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� ( + : Player�� �� , - : Floor�� ��)
		float mazino = fabs(objSize.y / 2.0f + floorSize.y / 2.0f);	// �� ��ü�� �������ֱ� ���� �ּҰŸ�

		// �浹ü�� Floor ��ü���� ���� ���� ��(�߽���ǥ ����)
		if (gap > 0)
		{
			// �� ��ü�� �����ִ� ���
			if (fabs(gap) < mazino)
			{
				objPos.y -= (mazino - fabs(gap)) - 2.5f;
				tr->SetPosition(objPos);
			}
			rb->SetGround(true);	// Floor ��ü�� �浹�� ��ü�� ���� �پ��ִ� ���·� ������ش�.
		}

		Papulatus* paulatus = dynamic_cast<Papulatus*>(_other->GetOwner());
		if (paulatus != nullptr)
		{
			int a = 0;
		}
	}

	void Floor::OnCollisionStay(Collider* _other)
	{
	}
	
	void Floor::OnCollisionExit(Collider* _other)
	{
		Player* player = dynamic_cast<Player*>(_other->GetOwner());
		_other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
		if (player != nullptr)
		{
			player->GetComponent<Rigidbody>()->SetGround(false);
			if (player->GetState() != eState::Rope && player->GetState() != eState::UpperCharge)
			{
				player->SetState(eState::Fall);
			}
		}
	}

}