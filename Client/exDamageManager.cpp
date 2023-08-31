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
#include "exMonsterDamageSkin.h"


// Component
#include "exTransform.h"
#include "exAnimator.h"

// PlayerSkill
#include "exRaisingblow.h"
#include "exRush.h"
#include "exUpperCharge.h"

namespace ex
{
	DamageManager::DamageManager(int _attackCount)
		: mDamageSize(0)
		, mPlayerDamage(0)
		, mDamageIndex(0)
		, mDamageIndexArr{}
		, mPlayerResultDamage(0)
		, mMonsterResultDamage(0)
		, mMonsterDamage(0)
		, mDamageCount(_attackCount)
	{
		Player* player = SceneManager::GetPlayer();
		int minDamage = (int)player->GetInfo()->mMinDamage;
		int maxDamage = (int)player->GetInfo()->mMaxDamage;
		mPlayerDamage = minDamage + std::rand() % (maxDamage - minDamage + 1);
	}

	DamageManager::~DamageManager()
	{
	}

	void DamageManager::Initialize()
	{
	}

	void DamageManager::Update()
	{
		UI::Update();
	}

	void DamageManager::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void DamageManager::PlayPlayerDamageAnimation(int _skillDamage, float _delay)
	{
		// resultDamage = �÷��̾��� MaxDamage ~ MinDamage ������ ���� �� * ��ų ������
		mPlayerResultDamage = mPlayerDamage * _skillDamage;


		int temp = mPlayerResultDamage;
		// �������� Size�� ���ϱ�
		std::string numStr = std::to_string(temp);
		mDamageSize = static_cast<int>(numStr.length());

		// �������� �ڿ����� �ϳ��� �ޱ����� ���� �迭
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = temp % 10;
			mDamageIndexArr.push_back(remainder);
			temp /= 10;
		}

		// �迭 �ٽ� ����� ����
		reverse(mDamageIndexArr.begin(), mDamageIndexArr.end());

		for (size_t j = 0; j < mDamageSize; j++)
		{
			DamageSkin* damageSkin = new DamageSkin(mDamageIndexArr[j]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, damageSkin);
			damageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			damageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (38.0f * j) - (mDamageSize * 38.0f / 2.0f));
			damageSkin->SetDamageDelay(_delay);
		}
	}

	void DamageManager::PlayMonsterDamageAnimation(int _monsterDamage, int _skillDamage)
	{
		// resultDamage = ������ Damage�� * ��ų ������
		mMonsterResultDamage = _monsterDamage * _skillDamage;

		int temp = mMonsterResultDamage;
		// �������� Size�� ���ϱ�
		std::string numStr = std::to_string(temp);
		mDamageSize = static_cast<int>(numStr.length());

		// �������� �ڿ����� �ϳ��� �ޱ����� ���� �迭
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = temp % 10;
			mDamageIndexArr.push_back(remainder);
			temp /= 10;
		}

		// �迭 �ٽ� ����� ����
		reverse(mDamageIndexArr.begin(), mDamageIndexArr.end());

		for (size_t i = 0; i < mDamageSize; i++)
		{
			MonsterDamageSkin* monsterDamageSkin = new MonsterDamageSkin(mDamageIndexArr[i]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, monsterDamageSkin);
			monsterDamageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			monsterDamageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (27.0f * i) - (mDamageSize * 31.0f / 2.0f));
		}
		Player* player = SceneManager::GetPlayer();
		player->GetInfo()->mHp -= mMonsterResultDamage;
		player->SetState(eState::Hit);
		player->SetInvincible(true);
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
