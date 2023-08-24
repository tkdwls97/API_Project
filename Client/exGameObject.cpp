#include "exGameObject.h"
#include "exSpriteRenderer.h"
#include "exCollider.h"
#include "exRigidbody.h"

namespace ex
{
	GameObject::GameObject()
		: mObjectState(eObjectState::Active)
	{
		// GameObject�� �⺻������ ��ġ������ ����ϱ� ������
		// Transform�� �����ڿ��� AddComponent���ش�
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			comp->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC _hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(_hdc);
		}
	}

	Transform* GameObject::GetTransform()
	{
		Transform* tr = nullptr;
		tr = GetComponent<Transform>();
		return tr;
	}

	void GameObject::OnCollisionEnter(Collider* _other)
	{
	}

	void GameObject::OnCollisionStay(Collider* _other)
	{
	}

	void GameObject::OnCollisionExit(Collider* _other)
	{
	}


}