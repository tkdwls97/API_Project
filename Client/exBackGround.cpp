#include "exBackGround.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"
#include "exSpriteRenderer.h"

namespace ex
{

	BackGround::BackGround()
	{
	}

	BackGround::~BackGround()
	{
	}

	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		float alpha = sr->GetAlpha();
		//alpha -= 0.2f * Time::GetDeltaTime();
		sr->SetAlpha(alpha);
	}

	void BackGround::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

}