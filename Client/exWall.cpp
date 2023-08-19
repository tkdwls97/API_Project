#include "exWall.h"
#include "exPlayer.h"
#include "exCollider.h"
#include "exRigidbody.h"
#include "exTransform.h"
#include "exMonsters.h"

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
	}

	void Wall::OnCollisionStay(Collider* _other)
	{
		GameObject* obj = _other->GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Rigidbody* rb = obj->GetComponent<Rigidbody>();
		Collider* col = obj->GetComponent<Collider>();
		Collider* col_this = GetComponent<Collider>();

		math::Vector2 objPos = tr->GetPosition();									// �浹ü�� ��ġ
		math::Vector2 floorPos = this->GetComponent<Transform>()->GetPosition();	// �ٴ� ��ü�� ��ġ
		math::Vector2 objSize = col->GetSize();										// �浹ü�� ������
		math::Vector2 thisSize = col_this->GetSize();								// Wall��ü�� ������
		math::Vector2 floorSize = this->GetComponent<Collider>()->GetSize();		// �ٴ� ��ü�� ũ��

		// x��
		float gapX = floorPos.x - objPos.x + 12.0f;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� (+ : ��ü�� ����, - : ��ü�� ������)
		float mazinoX = objSize.x / 2.0f + floorSize.x / 2.0f;		// �� ���� �������ֱ� ���� �ּҰŸ�
		// y��
		float gapY = floorPos.y - objPos.y;							// ���� �����ӿ��� �浹ü�� Floor ��ü�� �������ִ� �Ÿ� (+ : ��ü�� ����, - : ��ü�� ������)
		float mazinoY = objSize.y / 2.0f + floorSize.y / 2.0f;		// �� ���� �������ֱ� ���� �ּҰŸ�

		Player* player = dynamic_cast<Player*>(obj);
		//Monster* monster = dynamic_cast<Monster*>(obj);

		// �÷��̾�� �浹���� ���
		if (player != nullptr)
		{
			// Wall ��ü�� y�� ���̰� �� �� ��� (�Ϲ����� ���)
			if (thisSize.x < thisSize.y)
			{
				if (fabs(gapX) < mazinoX)
				{
					// ������ ��(+)
					if (gapX > 0)
					{
						objPos.x -= ((mazinoX - fabs(gapX)) - 1.0f);
						tr->SetPosition(objPos);
					}

					// �������� ��(-)
					if (gapX < 0)
					{
						objPos.x += ((mazinoX - fabs(gapX) + 20.0f) + 1.0f);
						tr->SetPosition(objPos);
					}
				}
			}
		}
	}
	void Wall::OnCollisionExit(Collider* _other)
	{
	}

}