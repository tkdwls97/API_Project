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
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			mGameObjects[i]->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			mGameObjects[i]->Render(_hdc);
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
