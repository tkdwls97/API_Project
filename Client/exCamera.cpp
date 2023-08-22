#include "exCamera.h"
#include "exTexture.h"
#include "exApplication.h"
#include "exTransform.h"
#include "exInput.h"
#include "exTime.h"

extern ex::Application application;

namespace ex
{
	// static ���� �����ʱ�ȭ
	math::Vector2			Camera::mResolution = math::Vector2::Zero;
	math::Vector2			Camera::mLookPosition = math::Vector2::Zero;
	math::Vector2			Camera::mDistance = math::Vector2::Zero;
	math::Vector2			Camera::mWidthLimit = math::Vector2::Zero;
	math::Vector2			Camera::mHeightLimit = math::Vector2::Zero;
	std::list<CameraEffect> Camera::mlistCamEffect = {};
	Texture*				Camera::mWhiteText = nullptr;
	Texture*				Camera::mBlackText = nullptr;
	float					Camera::mExceedX = 0.0f;
	float					Camera::mExceedY = 0.0f;

	bool Camera::mbColliderCheck = false;

	GameObject* Camera::mTargetObj = nullptr;
	//math::Vector2 Camera::mCameraLimit = math::Vector2::Zero;

	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
		mResolution = application.GetSize();

		// LookPositon(ī�޶� �ٶ󺸴� ��ġ)�� �ػ�x,y�� ���ݰ�(ȭ���� �߽�) ����
		// math.h���� operator/�� ���� ����
		mLookPosition = mResolution / 2.0f;

		mWhiteText = Texture::Create(L"WhiteTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(255, 255, 255));
		mBlackText = Texture::Create(L"BlackTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(0, 0, 0));

	}

	void Camera::Update()
	{
		if (Input::GetKeyDown(eKeyCode::Q))
		{
			if (mbColliderCheck)
			{
				mbColliderCheck = false;
			}
			else
			{
				mbColliderCheck = true;
			}

		}

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
			mExceedX = mWidthLimit.x - mDistance.x;
			mDistance.x = mWidthLimit.x;
		}
		else if (mDistance.x >= mWidthLimit.y)
		{
			mExceedX = mWidthLimit.y - mDistance.x;
			mDistance.x = mWidthLimit.y;
		}
		else
		{
			mExceedX = 0.0f;
		}

		if (mDistance.y <= mHeightLimit.x)
		{
			mExceedY = mHeightLimit.x - mDistance.y;
			mDistance.y = mHeightLimit.x;
		}
		else if (mDistance.y >= mHeightLimit.y)
		{
			mExceedY = mHeightLimit.y - mDistance.y;
			mDistance.y = mHeightLimit.y;
		}
		else
		{
			mExceedY = 0.0f;
		}
	}

	void Camera::Render(HDC _hdc)
	{
		// �̺�Ʈ ������ ����
		if (mlistCamEffect.empty())
		{
			return;
		}

		CameraEffect& effect = mlistCamEffect.front();

		effect.curTime += Time::GetDeltaTime();

		float ratio = effect.curTime / effect.duration;

		if (ratio < 0.f)
		{
			ratio = 0.f;
		}
		if (ratio > 1.f)
		{
			ratio = 1.f;
		}

		int alpha = 0;

		// �̺�Ʈ�� ���� ���İ��� ����
		if (effect.eEffect == CAMERA_EFFECT::FADE_OUT)
		{
			alpha = (int)(255.f * ratio);
		}
		else if (effect.eEffect == CAMERA_EFFECT::FADE_IN)
		{
			alpha = (int)(255.f * (1.f - ratio));
		}
		else if (effect.eEffect == CAMERA_EFFECT::Pause)
		{
			alpha = (int)255.f;
		}

		// AlphaBlend ���ð� ����
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER; // ������ ��� �̹����� ��ģ�ٴ� �ǹ�
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha; // ���� ���İ� ����

		if (effect.textColor == RGB(255, 255, 255))
		{
			::AlphaBlend(_hdc,
				0, 0
				, (int)mWhiteText->GetWidth()
				, (int)mWhiteText->GetHeight()
				, mWhiteText->GetHdc()
				, 0, 0
				, (int)mWhiteText->GetWidth()
				, (int)mWhiteText->GetHeight()
				, bf);
		}
		else if (effect.textColor == RGB(0, 0, 0))
		{
			::AlphaBlend(_hdc,
				0, 0
				, (int)mBlackText->GetWidth()
				, (int)mBlackText->GetHeight()
				, mBlackText->GetHdc()
				, 0, 0
				, (int)mBlackText->GetWidth()
				, (int)mBlackText->GetHeight()
				, bf);
		}


		if (effect.curTime > effect.duration)
		{
			effect.eEffect = CAMERA_EFFECT::NONE;
			mlistCamEffect.pop_front();
		}
	}

	void Camera::FadeIn(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::FADE_IN;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}

	void Camera::FadeOut(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::FADE_OUT;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}

	void Camera::Pause(float _duration, COLORREF _color)
	{
		CameraEffect ef = {};
		ef.eEffect = CAMERA_EFFECT::Pause;
		ef.duration = _duration;
		ef.curTime = 0.f;
		ef.textColor = _color;

		mlistCamEffect.push_back(ef);
	}
}