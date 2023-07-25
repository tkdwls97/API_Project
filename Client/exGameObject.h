#pragma once
#include "exEntity.h"
#include "exComponent.h"
#include "exTransform.h"

namespace ex
{
	class Collider;

	enum class eActionType
	{
		Idle,
		Walk,
		Jump,
		Attack,
		Rope,
	};

	// ������Ʈ�� ����
	enum class eObjectState
	{
		// Ȱ��ȭ ����, Update(OK), Render(OK)
		Active,
		// �����ִ� ����, Update(X), Render(X)
		Pause,
		// �̹� Render�� �������ǰ� �� ��ü�� �����Ǿ�� �ϴ� ���. Render�� ������ �� ��ü�� �����ϵ���. ex) Bullet.
		Dead,
		End,
	};



	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Jump,
			Down,
			DownJump,
			Rope,
			Attack,
			Skill,
			Death,
			End,
		};
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);

		template <typename T>
		T* AddComponent();
		template <typename T>
		T* GetComponent();

		Transform* GetTransform();

		void SetPosition(math::Vector2 pos) { GetTransform()->SetPosition(pos); }
		void SetPosition(float x, float y) { GetTransform()->SetPosition(x, y); }
		// ���� �Է��� ���� �� �ְ�
		void SetPositionX(float x) { GetTransform()->SetPositionX(x); }
		void SetPositionY(float y) { GetTransform()->SetPositionY(y); }

		// ������ ��ġ������ �������ִ� m_Pos ������ �������� �Լ�
		math::Vector2 GetPosition() { return GetTransform()->GetPosition(); }
		// ���� �Է��� ���� �� �ְ�
		float GetPositionX() { return GetTransform()->GetPositionX(); }
		float GetPositionY() { return GetTransform()->GetPositionY(); }

		// ȸ���� ������ ���� m_Rotation ������ �����ϴ� �Լ�
		void SetRotation(float rotation) { GetTransform()->SetRotation(rotation); }

		// ������ ������ ����ִ� m_Rotation�� �������� �Լ�
		float GetRotation() { return GetTransform()->GetRotation(); }

		virtual void OnCollisionEnter(Collider* _other);
		virtual void OnCollisionStay(Collider* _other);
		virtual void OnCollisionExit(Collider* _other);

	private:
		std::vector<Component*> mComponents;


	};

	template<typename T>
	__forceinline T* GameObject::AddComponent()
	{
		for (Component* com : mComponents)
		{
			Component* temp = dynamic_cast<T*>(com);
			if (temp != nullptr)
			{
				assert(nullptr);
			}
		}

		// ���� Component Ÿ���� ���ο� ��ü�� �����ϰ� 
		T* comp = new T();

		// vector<Component*> m_Components�� �־��ش�
		mComponents.push_back(comp);

		// �ش� �Ӽ��� ������ GameObject ��ü�� �˱�����
		// Component�� �ڽ��� ������ GameObject(this)�� ����Ű���ִ�.
		comp->SetOwner(this);

		return comp;
	}

	template<typename T>
	__forceinline T* GameObject::GetComponent()
	{
		// ���ø����� ���� Ÿ���� T* comp�� �����ϰ�
		T* comp = nullptr;

		// m_Components�ȿ� Component�� ��ӹ��� �ڽ�Ÿ���� �ִٸ�
		for (Component* c : mComponents)
		{
			// �ڽ�Ÿ�԰� TŸ���� ��ġ�Ѵٸ�
			// �ּҸ� ��ȯ �׷����ʴٸ� nullptr ��ȯ
			comp = dynamic_cast<T*>(c);

			// ���� Ÿ���� ����ȯ�� �����ߴٸ�
			if (comp != nullptr)
				return comp;
		}

		// ���ٸ� nullptr�� ����
		return comp;
	}
}

