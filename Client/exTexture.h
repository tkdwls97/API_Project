#pragma once
#include "exResource.h"

namespace ex
{
	enum class eTextureType
	{
		Bmp,
		AlphaBmp,
		Png,
		None,
	};

	// ���ҽ� Ŭ������ ��� �޴´�
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		void Render(HDC hdc
			, math::Vector2 _pos
			, math::Vector2 _size
			, math::Vector2 _leftTop
			, math::Vector2 _rightBottom
			, bool _affectCamera
			, math::Vector2 _scale = math::Vector2::One
			, float _alpha = 1.0f
			, float _rotate = 0.0f);


		// �θ� Ŭ������ Resource�� ���������Լ��� ������ �߻� Ŭ�����̱� ������
		// ����� �������� Load�Լ��� �������̵� �ؾ��Ѵ�
		virtual HRESULT Load(const std::wstring& _path) override;

		// �̹����� ���ΰ� ��ȯ(����� private�̱� ������ Get�Լ����)
		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT _width) { mWidth = _width; }
		// �̹����� ���ΰ� ��ȯ(����� private�̱� ������ Get�Լ����)
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT _height) { mHeight = _height; }

		COLORREF GetTexturePixel(int _x, int _y);

		math::Vector2 GetSize() { return math::Vector2(static_cast<float>(mWidth), static_cast<float>(mHeight)); }

		// ������� HDC��ȯ(����� private�̱� ������ Get�Լ����)
		HDC GetHdc() { return mHdc; }


		// �̹����� Ÿ��(bmp,png) ��ȯ
		eTextureType GetTextType() { return mTexType; }
		void SetTextType(eTextureType _type) { mTexType = _type; }

		Gdiplus::Image* GetImage() { return mImage; }
		
		HBITMAP GetBitmap() { return mBitmap; }
		void SetHBitmap(HBITMAP _bitmap) { mBitmap = _bitmap; }
		void SetHdc(HDC _hdc) { mHdc = _hdc; }

		static Texture* Create(const std::wstring& _name, UINT _width, UINT _height, COLORREF rgb = RGB(255, 255, 255));


	private:
		eTextureType mTexType;
		Gdiplus::Image* mImage;
		Gdiplus::Bitmap* mGdiBitMap;

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
		bool mbAffectCamera;


	};

}
