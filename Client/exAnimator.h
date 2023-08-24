#pragma once
#include "exComponent.h"
#include "exAnimation.h"

namespace ex
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		// ��Ʋ�� �̹����� ������ �ִϸ��̼��� �����Ҷ� ����ϴ� �Լ�
		Animation* CreateAnimation(const std::wstring& _name
			, class Texture* _texture
			, math::Vector2 _leftTop
			, math::Vector2 _size
			, math::Vector2 _interval
			, UINT _spriteLength
			, math::Vector2 _offset = math::Vector2::Zero
			, float _duration = 0.2f);

		// ���� ������ �̹����� �о�� �ִϸ��̼��� �����Ҷ� ����ϴ� �Լ�
		void CreateAnimationFolder(const std::wstring& _name
			, const std::wstring& _path
			, math::Vector2 _offset = math::Vector2::Zero
			, float _duration = 0.1f);


		// map������ ������ִ� m_Animations�� Ű���� ���ڷ� �־ ã���� �ּ� ��ȯ(Animation*)
		// ������ nullptr ��ȯ
		Animation* FindAnimation(const std::wstring& _name);
		
		bool IsActiveAnimationComplete() { return mActiveAnimation->IsComplete(); }

		void PlayAnimation(const std::wstring& _name, bool _loop = false);

		bool GetAffectedCamera() { return mbAffectedCamera; }
		void SetAffectedCamera(bool _enable) { mbAffectedCamera = _enable; }

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float _alpha) { mAlpha = _alpha; }

		math::Vector2 GetScale() { return mScale; }
		void SetScale(math::Vector2 scale) { mScale = scale; }


	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		bool m_bLoop;
		bool mbAffectedCamera;
		float mAlpha;
		math::Vector2 mScale;
	};

}
