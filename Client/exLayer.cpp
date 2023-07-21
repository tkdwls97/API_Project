#include "exLayer.h"

namespace ex
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
	}

	void Layer::Initialize()
	{
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Render(_hdc);
		}
	}
	std::vector<GameObject*>& Layer::GetGameObjects()
	{
		return mGameObjects;
	}
}
