#include "exTexture.h"
#include "exApplication.h"
#include "exResourceManager.h"
#include "exGameObject.h"
#include "exTransform.h"
#include "exCamera.h"

extern ex::Application application;

namespace ex
{
	// extern -> 어딘가에 있는 Application 클래스를 찾아서 전역변수를 만들어주기 위해
	// extern 사용
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



		// 기본 bmp
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
		// 만약 알파값(투명도)이 있는 bmp
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

		// png 파일
		else if (mTexType == eTextureType::Png)
		{
			//// 내가 원하는 픽셀을 투명화 시킬떄
			Gdiplus::ImageAttributes imageAtt = {};
			//// 투명화 시킬 픽셀 색 범위
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
		// 경로를 뒤에서부터 읽어서 확장자를 찾아 ext 변수에 복사한다.
		std::wstring ext = _path.substr(_path.find_last_of(L".") + 1);

		// 리소스가 bmp타입일때
		if (ext == L"bmp")
		{
			mTexType = eTextureType::Bmp;
			// LoadImageW() 아이콘, 커서, 애니메이션 커서 또는 비트맵을 로드합니다.
			// 내가 설정한 path(이미지의 경로)를 인자로 넘겨 HBITMAP으로 형 변환후 멤버 변수에 복사
			mBitmap = (HBITMAP)::LoadImageW(nullptr, _path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			// 복사 실패면 에러
			if (mBitmap == nullptr)
				return E_FAIL;

			// BITMAP타입 info 객체 생성
			BITMAP info = {};
			//GetObject 함수는 지정된 그래픽(내가 넘겨준 이미지) 개체에 대한 정보를 검색합니다.
			::GetObject(mBitmap, sizeof(BITMAP), &info);

			if (info.bmBitsPixel == 32)
			{
				mTexType = eTextureType::AlphaBmp;
			}

			// GetObject(핸들,
			// 버퍼에 쓸 바이트 크기,
			// 지정된 그래픽 개체에 대한 정보를 받는 버퍼에 대한 포인터 ) 


			//Texture클래스의 멤버변수에 받아온 가로 사이즈의 정보를 복사
			mWidth = info.bmWidth;
			//Texture클래스의 멤버변수에 받아온 세로 사이즈의 정보를 복사
			mHeight = info.bmHeight;


			// extern을 이용해 전역으로 만든 application의 GetHdc 이용하여 사용중이였던 HDC를
			// 새롭게 선언한 mainDC 변수에 대입한다
			HDC mainDC = application.GetHdc();

			// CreateCompatibleDC(기존 DC에 대한 핸들)
			// 지정된 장치와 호환 되는 DC를 만들어준다
			// 성공시 메모리DC에 대한 핸들 반환
			// 실패시 NULL 반환
			mHdc = ::CreateCompatibleDC(mainDC);

			// SelectObject(DC에 대한 핸들,선택할 개체에 대한 핸들)
			// 지정된 DC(디바이스 컨텍스트)로 개체를 선택한다.
			// 새 개체는 동일한 형식의 이전 개체를 대체한다.
			// 이 함수는 이전에 선택한 지정된 형식의 개체를 반환합니다. 
			// 애플리케이션은 새 개체로 그리기를 완료한 후 항상 새 개체를 원래의 기본 개체로 바꿔야 합니다.
			HBITMAP deafultBitmap = (HBITMAP)::SelectObject(mHdc, mBitmap);

			// 기존 디폴트 비트맵 삭제
			::DeleteObject(deafultBitmap);
		}
		// 리소스가 png타입일때
		else if (ext == L"png")
		{
			mTexType = eTextureType::Png;
			
			// image.png 파일을 이용하여 Texture 객체를 생성합니다.
			mImage = Gdiplus::Image::FromFile(_path.c_str());

			assert(mImage);

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		

		// 정상적으로 수행했음을 의미하는 S_OK를 반환
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

		// 인자로 들어온 색으로 채움
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}



}