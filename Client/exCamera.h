#pragma once
#include "exGameObject.h"

namespace ex
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// GameObject가 이동하는 좌표에 따라 카메라도 같이 이동하기위해 오차를 계산하는 함수
		static math::Vector2 CalculatePosition(math::Vector2 _pos) { return _pos - mDistance; }

		// 카메라가 바라보는 GameObject를 반환하는 함수
		static GameObject* GetTarget() { return mTargetObj; }
		
		// 멤버 변수 m_Target에 카메라로 지정할 GameObject를 세팅하는 함수
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

		// 화면 해상도
		static math::Vector2 mResolution;	

		// 카메라가 바라보고 있는 위치
		static math::Vector2 mLookPosition;

		// 가운데를 원점으로 이동한 거리
		static math::Vector2 mDistance;

		// 카메라가 바라보는 게임 오브젝트
		static GameObject* mTargetObj;

		static math::Vector2 mWidthLimit;
		static math::Vector2 mHeightLimit;
		static bool mbColliderCheck;

	};

	

}
