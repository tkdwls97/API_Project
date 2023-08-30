#pragma once
#include "exEntity.h"
#include "exLayer.h"



namespace ex
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC _hdc);

		virtual void SceneIN();
		virtual void SceneOut();


		Layer& GetLayer(enums::eLayerType _type);


		// ���� ���̾�Ÿ�� �迭�� �ε���(���̾� Ÿ��)�� ���� ������Ʈ�� �߰��Ѵ�
		void AddGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].AddGameObject(_gameObj);
		}

		void RemoveGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].RemoveGameObject(_gameObj);
		}

		void DeleteLayer(enums::eLayerType type)
		{
			// �ش� ���̾� ���� ������Ʈ�� ����
			mLayers[(int)type].DeleteObjects();
		}

		void RemoveLayer(enums::eLayerType type)
		{
			// �ش� ���̾� ���� ������Ʈ�� ����
			mLayers[(int)type].RemoveGameObjects();
		}

		void DeleteAllLayer()
		{
			// ��� ���̾��� ������Ʈ ����
			for (size_t i = 0; i < mLayers.size(); i++)
			{
				DeleteLayer((enums::eLayerType)i);
			}
		}

	private:
		std::vector<Layer> mLayers;
	};

}
