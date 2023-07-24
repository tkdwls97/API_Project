#include "exCamera.h"
#include "exApplication.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"


extern ex::Application application;
namespace ex
{
	// static 변수 전역초기화
	math::Vector2	Camera::mResolution		= math::Vector2::Zero;
	math::Vector2	Camera::mLookPosition	= math::Vector2::Zero;
	math::Vector2	Camera::mDistance		= math::Vector2::Zero;
	GameObject* Camera::mTargetObj			= nullptr;	

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

		// 위에 if문이 성공했으면 GameObject의 m_LookPosition(현재좌표)에
		// 윈도우 창 해상도 x,y의 절반값(카메라가 바라보는 곳의 초기값)을 뺀 값을
		// m_Distance에 복사(카메라가 바라보는곳(해상도 중심)에서 GameObject가 있는 좌표에
		// 카메라가 바라보는 곳을 옮긴다
		// 즉 카메라가 바라보는 곳과 실제 윈도우 창에 그려지는 GameObject의 오차거리를 구해서 저장한다 
		mDistance = mLookPosition - (mResolution / 2.0f);
	}

}