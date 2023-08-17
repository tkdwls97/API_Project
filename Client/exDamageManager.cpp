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

	void DamageManager::PlayDamageAnimation(int _skillDamage, float _delay)
	{
		// resultDamage = �÷��̾��� MaxDamage ~ MinDamage ������ ���� �� * ��ų ������
		int resultDamage = mPlayerDamage * _skillDamage;

		// �������� ��ȯ�� �����ϱ� ���� �������� ����
		int temp = resultDamage;

		// �������� �� ���̸� ���ϱ����� While��

		std::string numStr = std::to_string(temp);
		mDamageSize = numStr.length();

		// �������� �ڿ����� �ϳ��� �ޱ����� ���� �迭

		// tempArr�� ����
		for (size_t i = 0; i < mDamageSize; ++i)
		{
			int remainder = resultDamage % 10;
			mDamageIndexArr.push_back(remainder);
			resultDamage /= 10;
		}

		reverse(mDamageIndexArr.begin(), mDamageIndexArr.end());

		for (size_t j = 0; j < mDamageSize; j++)
		{
			DamageSkin* damageSkin = new DamageSkin(mDamageIndexArr[j]);
			object::ActiveSceneAddGameObject(enums::eLayerType::UI, damageSkin);
			damageSkin->GetComponent<Transform>()->SetPosition(this->GetPosition());
			damageSkin->GetComponent<Transform>()->SetPositionX(this->GetPositionX() + (38.0f * j) - (mDamageSize * 50.0f / 2.0f));
			damageSkin->SetDamageDelay(_delay);
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
