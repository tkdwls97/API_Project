#pragma once
#include "exEntity.h"
#include "exComponent.h"
#include "exTransform.h"
#include "exRigidbody.h"

namespace ex
{
	class Collider;

	//// ������Ʈ�� ����
	//enum class eObjectState
	//{
	//	// Ȱ��ȭ ����, Update(OK), Render(OK)
	//	Active,
	//	// �����ִ� ����, Update(X), Render(X)
	//	Pause,
	//	// �̹� Render�� �������ǰ� �� ��ü�� �����Ǿ�� �ϴ� ���. Render�� ������ �� ��ü�� �����ϵ���. ex) Bullet.
	//	Dead,
	//	End,
	//};
	


	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Idle,
			Move,
			Jump,
			DoubleJump,
			Down,
			Fall,
			Rope,
			RopeDown,
			Attack,
			Hit,
			Invincible,
			Death,
			JumpAttack,
			RaisingBlow,
			UpperCharge,
			Rush,
			ComboDeathFault,
			Buff,
			Stun,
			End,
		};

		enum class eMonsterState
		{
			Idle,
			Move,
			Attack,
			Chase,
			Hit,
			Dead,
			Skill1,
			Skill2,
			Skill3,
			Skill4,
			Skill5,
			Teleport,
			Sleep,
			WakeUp,

		};

		enum class eObjectState
		{
			Active,
			Pause,
			Dead,
			End,
		};

		friend static __forceinline void Destroy(GameObject* gameObject);

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

		void SetLayerType(enums::eLayerType _type) { mLayerType = _type; }
		enums::eLayerType GetLayerType() { return mLayerType; }

		eObjectState GetObjectState() { return mObjectState; }

	private:
		void death() { mObjectState = eObjectState::Dead; }
		void Pause() { mObjectState = eObjectState::Pause; }

	private:
		std::vector<Component*> mComponents;
		enums::eLayerType		mLayerType;
		eObjectState			mObjectState;

	};

	static __forceinline void Destroy(GameObject* gameObject)
	{
		gameObject->death();
	}




	// Component�� �߰� ���ִ� �Լ�
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

	// �߰��� Component�� �ִٸ� �������� �Լ�
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

