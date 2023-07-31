#include "exGameObject.h"
#include "exTransform.h"
#include "exSpriteRenderer.h"

namespace ex
{
	GameObject::GameObject()
	{
		// GameObject�� �⺻������ ��ġ������ ����ϱ� ������
		// Transform�� �����ڿ��� AddComponent���ش�
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
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