#include "exGameEffect.h"
#include "exAnimator.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exInput.h"
#include "exTransform.h"
#include "exTime.h"

namespace ex
{
	GameEffect::GameEffect()
	{
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimationFolder(L"PlayerLeftSwing",
			L"..\\Resources\\Maple\\Image\\Player\\Attack\\Weapon\\LEFT\\Swing");

		mAnimator->CreateAnimationFolder(L"PlayerRightSwing",
			L"..\\Resources\\Maple\\Image\\Player\\Attack\\Weapon\\RIGHT\\Swing");
	}

	GameEffect::~GameEffect()
	{
	}

	void GameEffect::Initialize()
	{
	}

	void GameEffect::Update()
	{
		GameObject::Update();
		
	}

	void GameEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GameEffect::PlayEffect(enums::eMoveDir _type)
	{
		// 분기할때 값을 보기위해 변수에 담아서 보는 것이 좋음
		std::wstring nextAnimWstr;
		if (_type == enums::eMoveDir::Left)
		{
			nextAnimWstr = L"PlayerLeftSwing";
		}
		else
		{
			nextAnimWstr = L"PlayerRightSwing";
		}

		// 제대로 키 값이 들어있다면
		if (!nextAnimWstr.empty())
		{			
			if (mAnimator)
			{
				mAnimator->PlayAnimation(nextAnimWstr, true);
			}
		}
	}

}