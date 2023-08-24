#include "exCollisionManager.h"
#include "exScene.h"
#include "exSceneManager.h"

namespace ex
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
		Clear();
	}

	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)
				{
					LayerCollision(activeScene, (enums::eLayerType)row, (enums::eLayerType)col);
				}
			}
		}
	}

	void CollisionManager::Render(HDC _hdc)
	{
	}

	void CollisionManager::Release()
	{
	}

	void CollisionManager::Clear()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			mLayerMasks[i].reset();
		}
		mCollisionMap.clear();
	}

	void CollisionManager::CollisionLayerCheck(enums::eLayerType _left, enums::eLayerType _right, bool _enable)
	{
		int row = -1;
		int col = -1;

		if (_left > _right)
		{
			row = (UINT)_left;
			col = (UINT)_right;
		}
		else
		{
			row = (UINT)_right;
			col = (UINT)_left;
		}

		mLayerMasks[row][col] = _enable;
	}

	void CollisionManager::LayerCollision(Scene* _scene, enums::eLayerType _left, enums::eLayerType _right)
	{
		// finds left layer objects
		Layer& leftLayer = _scene->GetLayer(_left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		Layer& rightLayer = _scene->GetLayer(_right);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// finds right layer Objects
		for (size_t i = 0; i < lefts.size(); ++i) // for each �ϸ� ����
		{
			Collider* leftCol = lefts[i]->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (size_t j = 0; j < rights.size(); ++j)
			{
				Collider* rightCol = rights[j]->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (lefts[i] == rights[j])
					continue;

				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* _left, Collider* _right)
	{
		// �� �浹ü�� ID�� Ȯ��
		ColliderID ID;
		ID.left = (UINT)_left->GetCollisionNumber();
		ID.right = (UINT)_right->GetCollisionNumber();
		


		// ���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(ID.id);

		// Ȥ�� �浹������ ���ٸ� �������ָ�ȴ�
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		//if (_left->GetCollisonCheck() || _right->GetCollisonCheck())
		//{
		//	return;
		//}

		// �浹�Լ� ȣ��
		if (Intersect(_left, _right))
		{
			// �浹 ���λ���
			if (iter->second == false)
			{
				_left->OnCollisionEnter(_right);
				_right->OnCollisionEnter(_left);

				iter->second = true;

			}
			else // ó�� �浹�ϴ� ����
			{
				_left->OnCollisionStay(_right);
				_right->OnCollisionStay(_left);
			}
		}
		else
		{
			// �浹�� ������������
			if (iter->second == true)
			{
				_left->OnCollisionExit(_right);
				_right->OnCollisionExit(_left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* _left, Collider* _right)
	{
		math::Vector2 leftPos = _left->GetPosition();
		math::Vector2 rightPos = _right->GetPosition();

		math::Vector2 leftSize = _left->GetSize();
		math::Vector2 rightSize = _right->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		{
			return true;
		}

		return false;
	}

	

}
