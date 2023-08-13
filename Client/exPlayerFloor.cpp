#include "exPlayerFloor.h"
#include "exSceneManager.h"
#include "exPlayer.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exRigidbody.h"

namespace ex
{
	PlayerFloor::PlayerFloor(GameObject*  _owner)
		: mOwner(_owner)
	{
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<Rigidbody>();

		mCollider->SetNomalCollor(RGB(0, 0, 255));
		mCollider->SetSize(math::Vector2(45.0f, 5.0f));
		mCollider->SetOffset(math::Vector2(-12.0f, 45.0f));
	}

	PlayerFloor::~PlayerFloor()
	{
	}

	void PlayerFloor::Initialize()
	{
	}

	void PlayerFloor::Update()
	{
		math::Vector2 pos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		mTransform->SetPosition(pos);

		// PlayerFloor와 Floor가 충돌하는 중이면 Player가 땅에 있다고 인식
		Player* player = SceneManager::GetPlayer();

		bool bCheack = mRigidbody->GetGround();
		//if (bCheack)
		//{
		//	player->GetComponent<Rigidbody>()->SetGround(true);
		//}
		//else
		//{
		//	player->GetComponent<Rigidbody>()->SetGround(false);
		//}

		GameObject::Update();
	}

	void PlayerFloor::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void PlayerFloor::OnCollisionEnter(Collider* _other)
	{
	}

	void PlayerFloor::OnCollisionStay(Collider* _other)
	{
	}

	void PlayerFloor::OnCollisionExit(Collider* _other)
	{
	}

}
