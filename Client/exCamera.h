#pragma once
#include "exGameObject.h"

namespace ex
{
	enum class  CAMERA_EFFECT
	{
		FADE_IN,
		FADE_OUT,
		Pause,
		NONE,
	};

	struct CameraEffect
	{
		CAMERA_EFFECT	eEffect;
		float			duration;
		float			curTime;
		COLORREF		textColor;
	};

	class Texture;

	class Camera
	{
	public:
		Camera();
		virtual ~Camera();

		static void Initialize();
		static void Update();
		static void Render(HDC _hdc);

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
		static math::Vector2 GetLookPosition() { return mLookPosition; }
		static bool GetColliderCheck() { return mbColliderCheck; }

		static float GetExceedX() { return mExceedX; }
		static float GetExceedY() { return mExceedY; }

		//static void SetLimitDistance(math::Vector2 CameraLimit)
		//{
		//	mCameraLimit = CameraLimit;
		//}

		static void FadeIn(float _duration, COLORREF _color);
		static void FadeOut(float _duration, COLORREF _color);
		static void Pause(float _duration, COLORREF _color);


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

		static float mExceedX;
		static float mExceedY;

		static bool mbColliderCheck;

		static std::list<CameraEffect>  mlistCamEffect;	// ī�޶� ȿ�� �̺�Ʈ ����Ʈ
		static  Texture* mWhiteText;				// ī�޶� ȿ���� �ؽ���
		static  Texture* mBlackText;				// ī�޶� ȿ���� �ؽ���

	};
}
