#include "exMonstersBar.h"
#include "exMonsters.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"


namespace ex
{
	MonstersBar::MonstersBar(Monsters* _owner)
		: mReductionHp(0.0f)
		, mMonstersHp(0)
		, mMonstersMaxHp(0)
	{
		mMonsters = dynamic_cast<Monsters*>(_owner);
		mMonstersHpBar = ResourceManager::Load<Texture>(L"MushMomHpBar", L"..\\Resources\\Maple\\Image\\UI\\MonsterHPBar.bmp");
		mMonsterEmptyHpBar = ResourceManager::Load<Texture>(L"MushMomHpBar", L"..\\Resources\\Maple\\Image\\UI\\MonsterEmptyBar.bmp");
	}

	MonstersBar::~MonstersBar()
	{
	}

	void MonstersBar::Initialize()
	{
	}

	void MonstersBar::Update()
	{
		mMonstersHp = mMonsters->GetMonstersInfo().mHp;
		mMonstersMaxHp = mMonsters->GetMonstersInfo().mMaxHp;

		if ((int)mReductionHp >= mMonstersHp)
		{
			mReductionHp -= (float)Time::GetDeltaTime() * 9000000.0f;
		}
		else
		{
			mReductionHp = (float)mMonstersHp;
		}
		UI::Update();
	}

	void MonstersBar::Render(HDC _hdc)
	{
		int hp = mMonstersHp;
		float fhp = (float)hp / mMonstersMaxHp;

		::TransparentBlt(_hdc, mMonsters->GetPositionX(), mMonsters->GetPositionY(), (int)(mMonstersHpBar->GetWidth() * fhp), mMonstersHpBar->GetHeight(), mMonstersHpBar->GetHdc()
			, 0, 0, (int)(mMonstersHpBar->GetWidth() * fhp), mMonstersHpBar->GetHeight(), RGB(255, 0, 255));

		UI::Render(_hdc);
	}

	void MonstersBar::OnCollisionEnter(Collider* _other)
	{
	}

	void MonstersBar::OnCollisionStay(Collider* _other)
	{
	}

	void MonstersBar::OnCollisionExit(Collider* _other)
	{
	}
}
