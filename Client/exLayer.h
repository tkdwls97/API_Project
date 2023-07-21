#pragma once
#include "exEntity.h"
#include "exGameObject.h"

namespace ex
{
	class Layer : public Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		
		void AddGameObject(GameObject* _gameObj)
		{
			mGameObjects.push_back(_gameObj);
		}

		std::vector<GameObject*>& GetGameObjects();

	private:
		std::vector<GameObject*> mGameObjects;
	};
}