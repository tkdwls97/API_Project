#include "exTexture.h"
#include "exApplication.h"
#include "exResourceManager.h"
#include "exGameObject.h"
#include "exTransform.h"
#include "exCamera.h"

extern ex::Application application;

namespace ex
{
	// extern -> ��򰡿� �ִ� Application Ŭ������ ã�Ƽ� ���������� ������ֱ� ����
	// extern ���
	Texture::Texture()
		: mImage(nullptr)
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
		, mTexType(eTextureType::None)
		, mbAffectCamera(true)
	
	{
	}
	Texture::~Texture()
	{
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	void Texture::Render(HDC hdc
		, math::Vector2 pos
		, math::Vector2 size
		, math::Vector2 leftTop
		, math::Vector2 rightBottom
		, bool _affectCamera
		, math::Vector2 scale
		, float alpha
		, float rotate)
	{
		if (mBitmap == nullptr && mImage == nullptr)
		{
			return;
		}
		
		if (_affectCamera)
		{
			pos = Camera::CalculatePosition(pos);
		}



		// �⺻ bmp
		if (mTexType == eTextureType::Bmp)
		{
			::TransparentBlt(hdc
				, (int)pos.x - (int)(size.x * scale.x / 2.0f)
				, (int)pos.y - (int)(size.y * scale.y / 2.0f)
				, (int)(size.x * scale.x)
				, (int)(size.y * scale.y)
				, mHdc
				, (int)leftTop.x
				, (int)leftTop.y
				, (int)rightBottom.x
				, (int)rightBottom.y
				, RGB(255, 0, 255));

		}
		// ���� ���İ�(����)�� �ִ� bmp
		else if (mTexType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;

			// 0.0f ~ 1.0f -> 0 ~ 255
			float alpha = 1.0f;
			alpha = std::floor(alpha * 255.0f);

			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = static_cast<BYTE>(alpha); // 0 ~ 255

			::AlphaBlend(hdc
				, (int)pos.x - (int)(size.x * scale.x / 2.0f)
				, (int)pos.y - (int)(size.y * scale.y / 2.0f)
				, (int)(size.x * scale.x)
				, (int)(size.y * scale.y)
				, mHdc
				, (int)leftTop.x
				, (int)leftTop.y
				, (int)rightBottom.x
				, (int)rightBottom.y
				, func);
		}

		// png ����
		else if (mTexType == eTextureType::Png)
		{
			//// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
			Gdiplus::ImageAttributes imageAtt = {};
			//// ����ȭ ��ų �ȼ� �� ����
			imageAtt.SetColorKey(Gdiplus::Color(100,100,100)
				, Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mImage
				, Gdiplus::Rect
				(
					(int)(pos.x - (size.x * scale.x / 2.0f))
					, (int)(pos.y - (size.y * scale.y / 2.0f))
					, (int)(size.x * scale.x)
					, (int)(size.y * scale.y)
				)
				, (int)leftTop.x
				, (int)leftTop.y
				, (int)rightBottom.x
				, (int)rightBottom.y
				, Gdiplus::UnitPixel
				, nullptr);

			//Gdiplus::Graphics graphics(hdc);
			//graphics.DrawImage(m_Texture->GetImage()
			//	, (int)(pos.x - (m_Texture->GetWidth() * m_Scale.x / 2.0f))
			//	, (int)(pos.y - (m_Texture->GetWidth() * m_Scale.y / 2.0f))
			//	, (int)(m_Texture->GetWidth() * m_Scale.x)
			//	, (int)(m_Texture->GetHeight() * m_Scale.y));
		}
	}


	HRESULT Texture::Load(const std::wstring& _path)
	{
		// ��θ� �ڿ������� �о Ȯ���ڸ� ã�� ext ������ �����Ѵ�.
		std::wstring ext = _path.substr(_path.find_last_of(L".") + 1);

		// ���ҽ��� bmpŸ���϶�
		if (ext == L"bmp")
		{
			mTexType = eTextureType::Bmp;
			// LoadImageW() ������, Ŀ��, �ִϸ��̼� Ŀ�� �Ǵ� ��Ʈ���� �ε��մϴ�.
			// ���� ������ path(�̹����� ���)�� ���ڷ� �Ѱ� HBITMAP���� �� ��ȯ�� ��� ������ ����
			mBitmap = (HBITMAP)::LoadImageW(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			// ���� ���и� ����
			if (mBitmap == nullptr)
				return E_FAIL;

			// BITMAPŸ�� info ��ü ����
			BITMAP info = {};
			//GetObject �Լ��� ������ �׷���(���� �Ѱ��� �̹���) ��ü�� ���� ������ �˻��մϴ�.
			::GetObject(mBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
			{
				mTexType = eTextureType::AlphaBmp;
			}

			// GetObject(�ڵ�,
			// ���ۿ� �� ����Ʈ ũ��,
			// ������ �׷��� ��ü�� ���� ������ �޴� ���ۿ� ���� ������ ) 


			//TextureŬ������ ��������� �޾ƿ� ���� �������� ������ ����
			mWidth = info.bmWidth;
			//TextureŬ������ ��������� �޾ƿ� ���� �������� ������ ����
			mHeight = info.bmHeight;


			// extern�� �̿��� �������� ���� application�� GetHdc �̿��Ͽ� ������̿��� HDC��
			// ���Ӱ� ������ mainDC ������ �����Ѵ�
			HDC mainDC = application.GetHdc();

			// CreateCompatibleDC(���� DC�� ���� �ڵ�)
			// ������ ��ġ�� ȣȯ �Ǵ� DC�� ������ش�
			// ������ �޸�DC�� ���� �ڵ� ��ȯ
			// ���н� NULL ��ȯ
			mHdc = ::CreateCompatibleDC(mainDC);

			// SelectObject(DC�� ���� �ڵ�,������ ��ü�� ���� �ڵ�)
			// ������ DC(����̽� ���ؽ�Ʈ)�� ��ü�� �����Ѵ�.
			// �� ��ü�� ������ ������ ���� ��ü�� ��ü�Ѵ�.
			// �� �Լ��� ������ ������ ������ ������ ��ü�� ��ȯ�մϴ�. 
			// ���ø����̼��� �� ��ü�� �׸��⸦ �Ϸ��� �� �׻� �� ��ü�� ������ �⺻ ��ü�� �ٲ�� �մϴ�.
			HBITMAP deafultBitmap = (HBITMAP)::SelectObject(mHdc, mBitmap);

			// ���� ����Ʈ ��Ʈ�� ����
			::DeleteObject(deafultBitmap);
		}
		// ���ҽ��� pngŸ���϶�
		else if (ext == L"png")
		{
			mTexType = eTextureType::Png;
			
			// image.png ������ �̿��Ͽ� Texture ��ü�� �����մϴ�.
			mImage = Gdiplus::Image::FromFile(_path.c_str());

			assert(mImage);

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		

		// ���������� ���������� �ǹ��ϴ� S_OK�� ��ȯ
		return S_OK;
	}

	COLORREF Texture::GetTexturePixel(int _x, int _y)
	{
		COLORREF rgb = ::GetPixel(mHdc, _x, _y);

		return rgb;
	}

	Texture* Texture::Create(const std::wstring& _name, UINT _width, UINT _height, COLORREF rgb)
	{
		Texture* image = ResourceManager::Find<Texture>(_name);
		if (image != nullptr)
			return image;

		image = new Texture();
		image->SetWidth(_width);
		image->SetHeight(_height);
		HDC hdc = application.GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, _width, _height);
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		image->SetName(_name);
		ResourceManager::Insert<Texture>(_name, image);

		// ���ڷ� ���� ������ ä��
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}



}