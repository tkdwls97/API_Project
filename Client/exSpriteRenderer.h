#pragma once
#include "exComponent.h"
#include "exTexture.h"


namespace ex
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		// �̹����� ��� ������ ������ �Լ�
		void SetImage(Texture* _texture) { mTexture = _texture; }
		Texture* GetImage() { return mTexture; }

		// �̹��� ũ�⿡ ���� ���� ������ �Լ�
		void SetScale(math::Vector2 _scale) { mScale = _scale; }
		void SetScaleX(float _scaleX) { mScale = _scaleX; }
		void SetScaleY(float _scaleY) { mScale = _scaleY; }

		// m_bAffectCamere�� ī�޶��� ������ �������� true or false�� ������ �Լ�
		void SetAffectCamera(bool _enable) { mbAffectCamere = _enable; }

		// ������ ��ȯ�� �Լ�
		float GetAlpha() { return mAlpha; }

		// ������ ������ �Լ�
		void SetAlpha(float _alpha) { mAlpha = _alpha; }

	private:
		// SpriteRenderer���� �̹����� �׸������� Texture*���� ����� �������ִ´�
		// ����� �̹����� �ּҸ� ������� ����
		Texture* mTexture;

		// �̹����� ũ�⸦ Ű������� x,y���� ������ ����
		math::Vector2 mScale;

		// ī�޶��� ������ �������� ���ϴ� boolŸ�� ����
		bool mbAffectCamere;

		// ȭ���� ������ ������ ���� (1.0f ���� 0�� �������� �� ��������)
		float mAlpha;
	};
}