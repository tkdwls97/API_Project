#pragma once
#include "exCommonInclude.h"
#include "exCollider.h"

namespace ex
{
#define LAYER_MAX (UINT)(enums::eLayerType::End)

	// left(UINT : 4Byte) + right(UINT : 4Byte)
	// ���� �� ������ UINT64 id�� �����Ѵ�.
	// �ֳĸ�....union�� ���� ū ��� ������ ũ�⸦ �������� ��� ����.
	//   |   left   |   right   |
	// ==|          id          |
	// ��ƴٸ� ����ü��� ���� ���� �޸� ������ ������ ����ϰ� �ִ� �����ϸ� �ȴ�.
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};


	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);
		static void Release();

		static void Clear();
		static void CollisionLayerCheck(enums::eLayerType _left, enums::eLayerType _right, bool _enable);
		static void LayerCollision(class Scene* _scene, enums::eLayerType _left, enums::eLayerType _right);
		static void ColliderCollision(Collider* _left, Collider* _right);
		static bool Intersect(Collider* _left, Collider* _right);


	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<LAYER_MAX> mLayerMasks[LAYER_MAX];
	};
}
