#pragma once
#include "exGameObject.h"

namespace ex
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// GameObject�� �̵��ϴ� ��ǥ�� ���� ī�޶� ���� �̵��ϱ����� ������ ����ϴ� �Լ�
		static math::Vector2 CalculatePosition(math::Vector2 pos) { return pos - mDistance; }

		// ī�޶� �ٶ󺸴� GameObject�� ��ȯ�ϴ� �Լ�
		static GameObject* GetTarget() { return mTargetObj; }
		
		// ��� ���� m_Target�� ī�޶�� ������ GameObject�� �����ϴ� �Լ�
		static void SetTarget(GameObject* target) { mTargetObj = target; }

	private:

		// ȭ�� �ػ�
		static math::Vector2 mResolution;	

		// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static math::Vector2 mLookPosition;

		// ����� �������� �̵��� �Ÿ�
		static math::Vector2 mDistance;

		// ī�޶� �ٶ󺸴� ���� ������Ʈ
		static GameObject* mTargetObj;


	};

}
