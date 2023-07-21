#pragma once
#include "exEntity.h"

namespace ex
{
	class GameObject;
	class Component : public Entity
	{
	public:	
		// Component�� ��ӹ��� Ŭ������ �θ� �����ڰ� ���ڸ� �ޱ⋚����
		// enum class�� ���ǵ� Ÿ������ type�� �ʱ�ȭ ������Ѵ�.
		Component(enums::eComponentType _type);
		virtual ~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);


		// Component�� ��ӹ��� Ŭ�������� ���θ� �����Ϸ� �Ҷ�
		// Component�� ���� ���� ������Ʈ�� ���� ������ �� �� �ְ� �����ν�
		// GameObjcet�� Component ���� ��ȣ�ۿ�� ���� �÷ο츦 ��Ȱ�ϰ� ������ �� �ְ� �˴ϴ�.
		void SetOwner(GameObject* _owner) { mOwner = _owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		const enums::eComponentType mType;
		GameObject* mOwner;
	};
}

