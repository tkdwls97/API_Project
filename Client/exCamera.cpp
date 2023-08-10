#include "exCamera.h"
#include "exApplication.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"


extern ex::Application application;
namespace ex
{
	// static 변수 전역초기화
	math::Vector2	Camera::mResolution = math::Vector2::Zero;
	math::Vector2	Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2	Camera::mDistance = math::Vector2::Zero;
	math::Vector2	Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2	Camera::mHeightLimit = math::Vector2::Zero;

	GameObject* Camera::mTargetObj = nullptr;
	//math::Vector2 Camera::mCameraLimit = math::Vector2::Zero;

	void Camera::Initialize()
	{
		mResolution = application.GetSize();

		// LookPositon(카메라가 바라보는 위치)에 해상도x,y의 절반값(화면의 중심) 복사
		// math.h에서 operator/을 만들어서 가능
		mLookPosition = mResolution / 2.0f;
	}

	void Camera::Update()
	{
		// 만약 GameObject* 타입 타겟이 있으면
		if (mTargetObj)
		{
			// 타겟의 이동값을 tr에 저장하겠다
			//Transform* tr = m_Target->GetComponent<Transform>();
			Transform* tr = mTargetObj->GetTransform();
			// tr(GameObject* mTarget)의 현재 좌표를 카메라가 바라보는 위치에 복사
			mLookPosition = tr->GetPosition();

		}
		else
		{
			// 타겟 설정이 nullptr이면 가운데를 바라보게 설정
			mLookPosition = math::Vector2(640.0f, 360.0f);
		}

		// 위에 if문이 성공했으면 GameObject의 m_LookPosition(현재좌표)에
		// 윈도우 창 해상도 x,y의 절반값(카메라가 바라보는 곳의 초기값)을 뺀 값을
		// m_Distance에 복사(카메라가 바라보는곳(해상도 중심)에서 GameObject가 있는 좌표에
		// 카메라가 바라보는 곳을 옮긴다
		// 즉 카메라가 바라보는 곳과 실제 윈도우 창에 그려지는 GameObject의 오차거리를 구해서 저장한다 
		mDistance = mLookPosition - (mResolution / 2.0f);

		// 이미지의 x의 왼쪽 최대 값 (이미지를 넘어서 윈도우 화면이 보이지않는 값)
		// 보다 작아지지 않게(왼쪽으로가면 -= x) 리미트 값으로 고정함
		if (mDistance.x <= mWidthLimit.x)
		{
			mDistance.x = mWidthLimit.x;
		}
		if (mDistance.x >= mWidthLimit.y)
		{
			mDistance.x = mWidthLimit.y;
		}

		if (mDistance.y <= mHeightLimit.x)
		{
			mDistance.y = mHeightLimit.x;
		}
		if (mDistance.y >= mHeightLimit.y)
		{
			mDistance.y = mHeightLimit.y;
		}

		//// 카메라 이동제한
		//if (mDistance.x < 0)
		//{
		//	mDistance.x = 0;
		//}

		//if (mDistance.y < 0)
		//{
		//	mDistance.y = 0;
		//}

		//if (mDistance.x > mCameraLimit.x - mResolution.x)
		//{
		//	mDistance.x = mCameraLimit.x - mResolution.x;
		//}

		//if (mDistance.y > mCameraLimit.y - mResolution.y)
		//{
		//	mDistance.y = mCameraLimit.y - mResolution.y;
		//}

	}

}