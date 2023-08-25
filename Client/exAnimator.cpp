#include "exAnimator.h"
#include "exResourceManager.h"
#include "exTexture.h"

namespace ex
{

	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mAlpha(1.0f)
		, mbAffectedCamera(true)
		, mScale(math::Vector2::One)
		, mActiveAnimation(nullptr)
		, m_bLoop(false)
	{
	}

	Animator::~Animator()
	{
 		for (auto& iter : mAnimations)
		{
			if (nullptr != iter.second)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && m_bLoop)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);

		}
	}

	Animation* Animator::CreateAnimation(const std::wstring& name
		, class Texture* texture
		, math::Vector2 leftTop, math::Vector2 size
		, math::Vector2 interval, UINT spriteLength
		, math::Vector2 offset, float duration)
	{

		//// �ִϸ��̼��� ����� ����� ���� �ʴ´�.
		//// ���� ���� �����ڸ� ���ؼ� �����ؼ� ó���Ѵ�.
		//// ù��° ��Ǹ� ������ �̹� ���� �ֱ⶧���� �ι�° ��Ǻ��ʹ� �������ʰԵȴ�
		//if (animation != nullptr)
		//{
		//	auto iter = m_Animations.find(name);
		//	if (iter == m_Animations.end())
		//	{
		//		animation = new Animation(*animation);
		//		if (animation)
		//		{
		//			animation->SetAnimator(this);
		//			m_Animations.insert(std::make_pair(name, animation));
		//			return;
		//		}
		//	}
		//	// ���⼭ �ٷ� return�� �ƴ϶� ��������Ÿ� ������ ��ߵǴµ�....
		//	return;
		//}
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
		{
			return animation;
		}

		animation = new Animation();
		animation->Create(name, texture
			, leftTop, size, interval, offset
			, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		return animation;

	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
		{
			return nullptr;
		}

		return iter->second;
	}

	void Animator::CreateAnimationFolder(const std::wstring& name
		, const std::wstring& path, math::Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCout = 0;

		std::filesystem::path fs(path);
		std::vector<Texture*> images = {};
		eTextureType tempType = eTextureType::None;

		// for each�� ���� 
		std::filesystem::recursive_directory_iterator it(fs);
		std::filesystem::recursive_directory_iterator end;
		//for (auto& p : std::filesystem::recursive_directory_iterator(path))
		for (; it != end; ++it)
		{
			std::wstring fileName = it->path().filename();
			std::wstring fullName = it->path();

			// �̹��� �ε�
			Texture* image = ResourceManager::Load<Texture>(fileName, fullName);
			tempType = image->GetTextType();

			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCout++;
		}

		Texture* spriteSheet = Texture::Create(name, width * fileCout, height);

		// Video �⺻ Ÿ�� Bmp�� ����
		spriteSheet->SetTextType(tempType);


		int idx = 0;
		for (Texture* image : images)
		{
			::BitBlt(spriteSheet->GetHdc(), width * idx, 0
				, image->GetWidth(), image->GetHeight()
				, image->GetHdc(), 0, 0, SRCCOPY);

			idx++;
		}

		CreateAnimation(name
			, spriteSheet, math::Vector2(0.0f, 0.0f)
			, math::Vector2(static_cast<float>(width), static_cast<float>(height))
			, math::Vector2(static_cast<float>(width), 0), fileCout, offset, duration);
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{

		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			return;
		}

		// ���� animation�� �ٽ� FindAnimation animation�� ������ ����
		if (mActiveAnimation == animation)
		{
			return;
		}

		mActiveAnimation = animation;
		// ���� animation�� ���͵� ���µǾ animation�� ������ �����������
		mActiveAnimation->Reset();
		m_bLoop = loop;

	}

}