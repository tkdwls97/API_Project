#include "exScene.h"
#include "exTime.h"

namespace ex
{
	Scene::Scene()
	{
		mLayers.resize((int)enums::eLayerType::End);
	}

	Scene::~Scene()
	{
		mLayers.clear();
	}

	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::Render(HDC _hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(_hdc);
		}
	}

	void Scene::SceneIN()
	{
	}

	void Scene::SceneOut()
	{
	}

	Layer& Scene::GetLayer(enums::eLayerType _type)
	{
		return mLayers[(UINT)_type];
	}
}
