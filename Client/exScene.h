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


		// 벡터 레이어타입 배열의 인덱스(레이어 타입)에 게임 오브젝트를 추가한다
		void AddGameObject(enums::eLayerType _type, GameObject* _gameObj)
		{
			mLayers[(int)_type].AddGameObject(_gameObj);
		}

	private:
		std::vector<Layer> mLayers;
	};

}
