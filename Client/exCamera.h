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
		static math::Vector2 CalculatePosition(math::Vector2 _pos) { return _pos - mDistance; }

		// ī�޶� �ٶ󺸴� GameObject�� ��ȯ�ϴ� �Լ�
		static GameObject* GetTarget() { return mTargetObj; }
		
		// ��� ���� m_Target�� ī�޶�� ������ GameObject�� �����ϴ� �Լ�
		static void SetTarget(GameObject* _target) { mTargetObj = _target; }

		static void SetLimitDistance(math::Vector2 _widthLimit, math::Vector2 _heightLimit)
		{
			mWidthLimit = _widthLimit;
			mHeightLimit = _heightLimit;
		}

		static math::Vector2 GetWidthLimit() { return mWidthLimit; }
		static math::Vector2 GetHeightLimit() { return mHeightLimit; }
		static bool GetColliderCheck() { return mbColliderCheck; }

		//static void SetLimitDistance(math::Vector2 CameraLimit)
		//{
		//	mCameraLimit = CameraLimit;
		//}

	private:

		// ȭ�� �ػ�
		static math::Vector2 mResolution;	

		// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static math::Vector2 mLookPosition;

		// ����� �������� �̵��� �Ÿ�
		static math::Vector2 mDistance;

		// ī�޶� �ٶ󺸴� ���� ������Ʈ
		static GameObject* mTargetObj;

		static math::Vector2 mWidthLimit;
		static math::Vector2 mHeightLimit;
		static bool mbColliderCheck;

	};

	

}
