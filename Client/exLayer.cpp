#include "exLayer.h"

namespace ex
{
	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
		for (size_t i = 0; i < mGameObjects.size(); i++)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
				continue;

			mGameObjects[i]->Initialize();
		}
	}

	void Layer::Update()
	{
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
			{
				continue;
			}
			mGameObjects[i]->Update();
		}
	}

	void Layer::Render(HDC _hdc)
	{
		for (size_t i = 0; i < mGameObjects.size(); ++i)
		{
			if (mGameObjects[i]->GetObjectState() == GameObject::eObjectState::Pause)
			{
				continue;
			}

			mGameObjects[i]->Render(_hdc);
		}

		// Dead ������Ʈ�� Layer���� ����
		for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ((*iter)->GetObjectState() == GameObject::eObjectState::Dead)
			{
				GameObject* obj = *iter;
				iter = mGameObjects.erase(iter);
				delete obj;
				obj = nullptr;
			}
			else
			{
				iter++;
			}
		}
	}


	void Layer::RemoveGameObject(GameObject* _gameObj)
	{
		// mGameObjects ������ �ش� ������Ʈ�� iterator �� ã�ƿ´�
		std::vector<GameObject*>::iterator iter = find(mGameObjects.begin(), mGameObjects.end(), _gameObj);
		// mGameObjects���� ���� �ش� ������Ʈ�� �����Ѵٸ� �����Ѵ�
		if (iter != mGameObjects.end())
			mGameObjects.erase(iter);
	}

	void Layer::RemoveGameObjects()
	{
		mGameObjects.clear();
	}

	std::vector<GameObject*>& Layer::GetGameObjects()
	{
		return mGameObjects;
	}

	void Layer::DeleteObjects()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr != obj)
			{
				delete obj;
				obj = nullptr;
			}
		}
		mGameObjects.clear();
	}
}
