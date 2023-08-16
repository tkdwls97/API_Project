#include "exAnimation.h"
#include "exTexture.h"
#include "exAnimator.h"
#include "exTime.h"
#include "exTransform.h"
#include "exGameObject.h"
#include "exCamera.h"

namespace ex
{
	// �ʱ�ȭ
	Animation::Animation()
		: mAnimator(nullptr)
		, mTexture(nullptr)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}

	// ���޹��� Animation�� ���� ����� �����س���.
	Animation::Animation(const Animation& _anim)
		: mAnimator(nullptr)
		, mTexture(_anim.mTexture)
		, mIndex(-1)
		, mTime(_anim.mTime)
		, mbComplete(false)
	{
		// �׳� �� ������(�ϰ� �ٽ� Ȯ���غ�) �����ϱ� ���ؼ� �����迭�� resize()�� ������ ũ�⸦ �������ش�.
		mSpriteSheet.resize(_anim.mSpriteSheet.size());

		// ���޹��� �ִϸ��̼��� �����ϰ� �ִ� Sprite Sheet�� ���ۺ��� �������� �����ͼ�
		// �������ش�.
		std::copy(_anim.mSpriteSheet.begin(), _anim.mSpriteSheet.end(), mSpriteSheet.begin());
	}

	Animation::~Animation()
	{
	}

	void Animation::Initialize()
	{
	}


	void Animation::Update()
	{
		// �Ϸ�Ǿ����� �� �̻� ����� �ʿ䰡 �����Ƿ� �������� ������ �� ���� ����.
		if (mbComplete)
		{
			return;
		}

		// Time Ŭ�����κ��� ��ŸŸ���� �޾ƿͼ� ���� �������� �ǰ� �� ���� ��� �ð��� �����ش�.
		mTime += Time::GetDeltaTime();
		// ���� ����� ������ ��Ʈ�� duration���� �ش� �������� �ǰ� �� ���� �ð��� �� ũ�ٸ�
		// ���� ���������� �����ؾ� �Ѵ�.
		if (mSpriteSheet[mIndex].duration < mTime)
		{
			// �������� ����� ���̹Ƿ� �����ð��� ���õ� ������ m_Time�� 0.f�� �ʱ�ȭ���ش�.
			mTime = 0.0f;

			// m_Index�� 0 ���� �����ϹǷ� ũ���� -1���� �۴ٸ� �ε����� ���������ش�.
			if (mIndex < mSpriteSheet.size() - 1)
			{
				mIndex++;
			}
			// else�� ���ų� ũ�ٴ� ���̹Ƿ� ������ �����ӿ� ������ ���̱� ������ m_bComplete��
			// true�� �ٲ��ش�.
			else
			{
				mbComplete = true;
			}
		}
	}

	// ���޹��� HDC�� �̿��Ͽ� �������� �׷�����.
	void Animation::Render(HDC _hdc)
	{
		// �׷��� �� ������ ��Ʋ�� �ؽ�ó�� nullptr�̶�� �������� �ʴ� ���̹Ƿ�
		// ����ó���� ���ؼ� return ó��
		if (mTexture == nullptr)
		{
			return;

		}

		// ���� index�� Sprite ������ �����´�.
		Sprite sprite = mSpriteSheet[mIndex];

		// ����ó���� ���� ó��
		if (nullptr == mAnimator)
		{
			return;
		}

		// Ʈ������ ������Ʈ�� ������ ����� GameObject�� �����ϴ� ����ۿ� ���µ�
		// GameObject�� �����ϱ� ���ؼ� �����ϰ� �ִ� m_Animator�κ��� GetOwner()�� ȣ���Ͽ�
		// Transform�� ������ ������ ����Ǵ� GameObject�� �����Ѵ�.
		// �� �������� GetComponent<Transform>()���� �ش� GameObject�� ������ Transform ��ü�� �����´�.
		GameObject* owner = mAnimator->GetOwner();
		// ����ó��
		if (!owner)
		{
			return;
		}

		Transform* tr = mAnimator->GetOwner()->GetComponent<Transform>();
		// ����ó��
		if (!tr)
		{
			return;
		}

		// ��ġ�� Ʈ���������κ��� �������� ���� �����ӿ� offset ���� ���ؼ� �׷��� ���� ��ġ�� ���Ѵ�.
		math::Vector2 pos = tr->GetPosition() + sprite.offset;

		// m_Texture�� �����ؼ� Render �Լ��� ȣ���Ѵ�.
		mTexture->Render(_hdc
			, pos
			, sprite.size
			, sprite.leftTop
			, sprite.size
			, mAnimator->GetAffectedCamera()
			, mAnimator->GetScale()
			, mAnimator->GetAlpha());
	}

	// ���޹��� ���ڸ� �̿��ؼ� m_SpriteSheet�� ���� ������ ������ �־��ش�.
	// �ٵ�, �� �Լ��� �ִϸ��̼��� ���� ��, �� �ٷ� �������� ã�Ƴ��� �־��ش�.
	void Animation::Create(const std::wstring& _name, Texture* _texture
		, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _interval, math::Vector2 _offset
		, UINT _spriteLength, float _duration)
	{
		SetName(_name);
		mTexture = _texture;


		for (UINT i = 0; i < _spriteLength; i++)
		{
			int temp = i;

			// �̹����� �ڿ��� ���� �о�� �� ��� 1�� �ε������� �а� ������ش�.
			if (0 > _interval.x)
			{
				++temp;
			}

			Sprite sprite = {};

			sprite.leftTop.x = _leftTop.x + (_interval.x * temp);
			sprite.leftTop.y = _leftTop.y;
			// ��Ʋ�� �̹����� �� ������ ������ ���� �̾�����
			// ������ �ؽ�ó�� �̹����� ���� ���̸� �Ѿ �����ٿ��� �ٽ� �о�� �Ұ��
			if (sprite.leftTop.x > _texture->GetWidth())
			{
				sprite.leftTop.x = sprite.leftTop.x - _texture->GetWidth();
				sprite.leftTop.y = _leftTop.y + _size.y;
			}
			sprite.size = _size;
			sprite.offset = _offset;
			sprite.duration = _duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}

}
