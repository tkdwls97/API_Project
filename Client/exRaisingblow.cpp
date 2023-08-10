#include "exRaisingblow.h"
#include "exTexture.h"
#include "exResourceManager.h"
#include "exAnimator.h"
#include "exTransform.h"
#include "exCollider.h"
#include "exTime.h"
#include "exPlayer.h"
#include "exSceneManager.h"
#include "exCollisionManager.h"
#include "exObject.h"
#include "exAnimation.h"
#include "exMonsters.h"


namespace ex
{
	Raisingblow::Raisingblow(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();

		//// png
		Texture* image = ResourceManager::Load<Texture>(L"LeftRaisingblow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Left\\LeftRaisingblow.png");

		//Texture* image = ResourceManager::Load<Texture>(L"LeftRaisingblow"
		//		, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Left\\LeftRaisingblow.bmp");

		mAnimator->CreateAnimation(L"LeftRaisingblow", image, math::Vector2(0.0f, 0.0f), math::Vector2(924.0f, 562.0f)
			, math::Vector2(924.0f, 562.0f), 14, math::Vector2(0), 0.015f);

		//// png
		//image = ResourceManager::Load<Texture>(L"RightRaisingblow"
		//	, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Right\\RightRaisingblow.png");

		image = ResourceManager::Load<Texture>(L"RightRaisingblow"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\Raisingblow\\Right\\RightRaisingblow.bmp");

		mAnimator->CreateAnimation(L"RightRaisingblow", image, math::Vector2(12936.0f, 0.0f), math::Vector2(924.0f, 562.0f)
			, math::Vector2(-924.0f, 0.0f), 14, math::Vector2(0), 0.05f);

		mAnimator->SetScale(math::Vector2(0.85f, 0.70f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();
		
		mCollider->SetSize(math::Vector2(270.0f,150.0f));
		mTransform->SetPosition(math::Vector2(playerPos));

		if (playerDir == enums::eMoveDir::Left)
		{
			mCollider->SetOffset(math::Vector2(-130.0f, -23.0f));
			mAnimator->PlayAnimation(L"LeftRaisingblow", false);
		}
		else
		{
			mCollider->SetOffset(math::Vector2(130.0f, -23.0f));
			mAnimator->PlayAnimation(L"RightRaisingblow", false);
		}

	}

	Raisingblow::~Raisingblow()
	{
	}

	void Raisingblow::Initialize()
	{
	}

	void Raisingblow::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		eState playerState = SceneManager::GetPlayer()->GetState();
		bool bCheck = mAnimator->IsActiveAnimationComplete();
		if (playerState == eState::RaisingBlow)
		{
			// 충돌 이벤트구현
		}
		else
		{
			// 어택이 끝나면 초기화해줌
			mAttackList.clear();
		}
		GameObject::Update();
	}

	void Raisingblow::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void Raisingblow::OnCollisionEnter(Collider* _other)
	{
	}

	void Raisingblow::OnCollisionStay(Collider* _other)
	{

	}

	void Raisingblow::OnCollisionExit(Collider* _other)
	{
	}
}