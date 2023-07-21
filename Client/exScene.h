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

		Layer& GetLayer(enums::eLayerType _type);


		// ���� ���̾�Ÿ�� �迭�� �ε���(���̾� Ÿ��)�� ���� ������Ʈ�� �߰��Ѵ�
		void AddGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].AddGameObject(_gameObj);
		}

	private:
		std::vector<Layer> mLayers;
	};

}
