#include "exCamera.h"
#include "exApplication.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"


extern ex::Application application;
namespace ex
{
	// static ���� �����ʱ�ȭ
	math::Vector2	Camera::mResolution = math::Vector2::Zero;
	math::Vector2	Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2	Camera::mDistance = math::Vector2::Zero;
	math::Vector2	Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2	Camera::mHeightLimit = math::Vector2::Zero;
	GameObject* Camera::mTargetObj = nullptr;

	void Camera::Initialize()
	{
		mResolution = application.GetSize();

		// LookPositon(ī�޶� �ٶ󺸴� ��ġ)�� �ػ�x,y�� ���ݰ�(ȭ���� �߽�) ����
		// math.h���� operator/�� ���� ����
		mLookPosition = mResolution / 2.0f;
	}

	void Camera::Update()
	{
		// ���� GameObject* Ÿ�� Ÿ���� ������
		if (mTargetObj)
		{
			// Ÿ���� �̵����� tr�� �����ϰڴ�
			//Transform* tr = m_Target->GetComponent<Transform>();
			Transform* tr = mTargetObj->GetTransform();
			// tr(GameObject* mTarget)�� ���� ��ǥ�� ī�޶� �ٶ󺸴� ��ġ�� ����
			mLookPosition = tr->GetPosition();

		}
		else
		{
			// Ÿ�� ������ nullptr�̸� ����� �ٶ󺸰� ����
			mLookPosition = math::Vector2(640.0f, 360.0f);
		}


		// ���� if���� ���������� GameObject�� m_LookPosition(������ǥ)��
		// ������ â �ػ� x,y�� ���ݰ�(ī�޶� �ٶ󺸴� ���� �ʱⰪ)�� �� ����
		// m_Distance�� ����(ī�޶� �ٶ󺸴°�(�ػ� �߽�)���� GameObject�� �ִ� ��ǥ��
		// ī�޶� �ٶ󺸴� ���� �ű��
		// �� ī�޶� �ٶ󺸴� ���� ���� ������ â�� �׷����� GameObject�� �����Ÿ��� ���ؼ� �����Ѵ� 
		mDistance = mLookPosition - (mResolution / 2.0f);



		// �̹����� x�� ���� �ִ� �� (�̹����� �Ѿ ������ ȭ���� �������ʴ� ��)
		// ���� �۾����� �ʰ�(�������ΰ��� -= x) ����Ʈ ������ ������
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

	}

}