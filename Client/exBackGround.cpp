#include "exBackGround.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"
#include "exSpriteRenderer.h"
#include "exResourceManager.h"
#include "exObject.h"

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

	void BackGround::SetAutoCameraLimit()
	{
		// 
		SpriteRenderer* bgsr = this->GetComponent<SpriteRenderer>();

		if (nullptr == bgsr)
		{
			return;
		}
		Texture* image = bgsr->GetImage();

		if (nullptr == image)
		{
			return;
		}
	
	
		math::Vector2 pos = this->GetComponent<Transform>()->GetPosition();
		math::Vector2 imageSize = image->GetSize() / 2.0f;

		math::Vector2 tempLimit = pos - imageSize;

		tempLimit.x = std::fabsf(tempLimit.x);
		tempLimit.y = std::fabsf(tempLimit.y);

		mCameraLimitLeft = -tempLimit.x;
		mCameraLimitRight = tempLimit.x;

	}

}