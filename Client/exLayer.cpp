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
			if (obj->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			obj->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			if (obj->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			obj->Render(_hdc);
		}

		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetObjectState() == GameObject::eObjectState::Dead)
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	
	std::vector<GameObject*>& Layer::GetGameObjects()
	{
		return mGameObjects;
	}
}
