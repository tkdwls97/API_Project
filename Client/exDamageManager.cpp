#include "exDamageManager.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
#include "exPlayer.h"
#include "exDamageSkin.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRush.h"
#include "exUpperCharge.h"

namespace ex
{
	DamageManager::DamageManager()
		: mDamageArr{}
		, mDamageSize(0)
		, mPlayerDamage(0)
		, mDamageIndex(0)
		, mDamageIndexArr{}
	{
		Player* player = SceneManager::GetPlayer();
		int minDamage = player->GetInfo()->mMinDamage;
		int maxDamage = player->GetInfo()->mMaxDamage;
		mPlayerDamage = minDamage + std::rand() % (maxDamage - minDamage + 1);
	}

	DamageManager::~DamageManager()
	{
	}

	void DamageManager::Initialize()
	{
	}

	void DamageManager::PlayDamageAnimation(int _skillDamage)
	{
		mDamageSize = 0;
		// resultDamage = 플레이어의 MaxDamage ~ MinDamage 사이의 랜덤 값 * 스킬 데미지
		int resultDamage = mPlayerDamage * _skillDamage;

		// 데미지값 변환을 방지하기 위한 데미지값 복사
		int temp = resultDamage;

		// 데미지의 총 길이를 구하기위한 While문
		while (temp != 0)
		{
			temp /= 10;
			++mDamageSize;
		}

		// 데미지를 뒤에부터 하나씩 받기위해 만든 배열
		int tempArr[10] = {};

		// tempArr에 저장
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = resultDamage % 10;
			tempArr[i] = remainder;
			resultDamage /= 10;
		}

 		int index = mDamageSize - 1;
		// 멤버 배열에 다시 정렬
		for (size_t i = 0; i < mDamageSize; i++)
		{
			mDamageIndexArr[i] = tempArr[index];
			--index;
		}

		for (size_t j = 0; j < mDamageSize; j++)
		{
			DamageSkin* damageSkin = new DamageSkin(mDamageIndexArr[j]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, damageSkin);
			damageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			damageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (50.0f * j) - (mDamageSize * 50.0f / 2.0f));
		}

	}


	void DamageManager::Update()
	{
		GameObject::Update();
	}

	void DamageManager::Render(HDC _hdc)
	{
		GameObject::Render(_hdc);
	}

	void DamageManager::OnCollisionEnter(Collider* _other)
	{
	}

	void DamageManager::OnCollisionStay(Collider* _other)
	{
	}

	void DamageManager::OnCollisionExit(Collider* _other)
	{
	}

}
