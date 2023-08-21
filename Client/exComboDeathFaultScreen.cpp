#include "exComboDeathFaultScreen.h"
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
#include "exDamageManager.h"
#include "exComboDeathFaultScreen.h"
#include "exComboDeathFaultHit.h"
#include "exCamera.h"


namespace ex
{
	ComboDeathFaultScreen::ComboDeathFaultScreen(GameObject* _owner)
		: EffectManger(_owner)
		, mOwner(_owner)
	{
		mComboDeathFaultInfo.AttackCount = 14;
		mComboDeathFaultInfo.DamagePercentage = 800;
		SetEffectInfo(mComboDeathFaultInfo);
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = AddComponent<Collider>();
		//// png
		Texture* image = ResourceManager::Load<Texture>(L"ComboDeathFaultLeftScreen"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Screen\\Left\\Left_ComboDeathFault_Screen.png");

		mAnimator->CreateAnimation(L"ComboDeathFaultLeftScreen", image, math::Vector2(0.0f, 0.0f), math::Vector2(1370.0f, 768.0f)
			, math::Vector2(1370.f, 768.f), 48, math::Vector2(0.0f, 0.0f), 0.05f);

		//// png
		image = ResourceManager::Load<Texture>(L"ComboDeathFaultRightScreen"
			, L"..\\Resources\\Maple\\Image\\Player2\\Skill\\ComboDeathFault\\ComboDeathFault_Screen\\Right\\Right_ComboDeathFault_Screen.png");

		mAnimator->CreateAnimation(L"ComboDeathFaultRightScreen", image, math::Vector2(64390.f, 0.0f), math::Vector2(1370.0f, 768.0f)
			, math::Vector2(-1370.0f, 0.0f), 48, math::Vector2(0.0f, 0.0f), 0.05f);

		mAnimator->SetScale(math::Vector2(1.0f, 1.2f));
		enums::eMoveDir playerDir = _owner->GetTransform()->GetMoveDir();
		math::Vector2 playerPos = _owner->GetPosition();

		mTransform->SetPosition(math::Vector2(playerPos));
		mAnimator->SetAffectedCamera(true);
		mCollider->SetSize(1280.0f, 720.0f);
		if (playerDir == enums::eMoveDir::Left)
		{
			mAnimator->PlayAnimation(L"ComboDeathFaultLeftScreen", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"ComboDeathFaultRightScreen", false);
		}

	}

	ComboDeathFaultScreen::~ComboDeathFaultScreen()
	{
	}

	void ComboDeathFaultScreen::Initialize()
	{
	}

	void ComboDeathFaultScreen::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
		GameObject::Update();
	}

	void ComboDeathFaultScreen::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void ComboDeathFaultScreen::OnCollisionEnter(Collider* _other)
	{
		Monsters* monsters = dynamic_cast<Monsters*>(_other->GetOwner());
		if (monsters != nullptr)
		{
			ComboDeathFaultHit* comboDeathFaultHit = new ComboDeathFaultHit(_other->GetOwner());
			object::ActiveSceneAddGameObject(enums::eLayerType::Effect, comboDeathFaultHit);
			for (size_t i = 1; i <= this->GetEffectInfo().AttackCount; i++)
			{
				DamageManager* damage = new DamageManager();
				damage->SetPosition(math::Vector2(monsters->GetPositionX(), monsters->GetPositionY() - 28.0f * i));
				damage->PlayPlayerDamageAnimation(this->GetEffectInfo().DamagePercentage, 0.15f * (i - 1));

				monsters->ReductiongHp(damage->GetPlayerResultDamage());
			}
		}
	}

	void ComboDeathFaultScreen::OnCollisionStay(Collider* _other)
	{

	}

	void ComboDeathFaultScreen::OnCollisionExit(Collider* _other)
	{
	}
}