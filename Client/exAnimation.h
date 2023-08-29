#pragma once
// Resource�� ��ӹޱ� ���ؼ� Resource.h ��� ����
#include "exResource.h"

namespace ex
{
	// ���漱�� �߰�
	class Texture;
	class Animator;

	// Animation Ŭ������ public���� Resource�� ��ӹ޴´�.
	class Animation : public Resource
	{
	public:
		// public���� ����ü Sprite�� �����Ѵ�.
		// Sprite�� �ִϸ��̼��� �� �������� �ǹ��Ѵٰ� �����ϸ� �ȴ�.
		// http://popkon.konkuk.ac.kr/news/articleView.html?idxno=10836 �����ӿ� ���� ����
		struct Sprite
		{
			// Sprite�� �Ϲ������� ��Ʋ�� �̹����� ����Ѵٰ� �����ϱ� ������ �ش� �������� ������
			// ��������� �� �ʿ䰡 �����Ѵ�.
			// Atlas Image�� ���� ���� ������ �̹����� ��Ƶ� �Ŵ��� �̹��� �����̴�.
			// Atlas Image�� �����ϴ� ������ �޸��� �������� �����̴�.
			// �Ϲ������� ��ǻ�� �������� CPU�� �������� ���θ� �����ϴ� ���� ���� ����̰�
			// �� ������ �츮�� �ƴ� ��(Memory)�� �����ϴ� ���� ������
			// �� �������� �츮�� �ƴ� �ϵ��ũ Ȥ�� SSD�� �����ϴ� ���� ������.
			// �̹��� ������ �ϵ��ũ Ȥ�� SSD�� �����ؼ� ������ �а� �̸� ��(Memory)�� �ø��� �����̱�
			// ������ ��Ʋ�� �̹����� ���� ���� ������ �̹����� ���ļ� ����ϴ� ���� ��ȣ�ϰ� �Ǿ���.
			// �� ���� ���� ������ �̹����� �� ���� �ϳ� �ϳ��� �̷���� �ִٸ� �̸� �д� �ð��� ����
			// �ʿ������� ���ʿ��� �ε� �ð��� �����ϰ� �ȴ�. �̷��� ���ʿ��� �ð� Ȥ�� ����� ���������
			// �Ѵ�.

			// LeftTop : �»���� ��ġ ��ǥ
			math::Vector2 leftTop;
			// Size : �»�����κ��� ���ϴܱ����� ũ��
			math::Vector2 size;
			// offset : ������ ��ġ�� �����ؼ� �׷��ֱ� ���� ������ ������ ��
			math::Vector2 offset;
			// duration : �ش� �������� ���(����)�� �ð�(���� �ð��̶�� �����ϸ� �ȴ�)
			float duration;

			// Sprite�� �ʱ�ȭ�� ���� ����ü ������
			Sprite()
				: leftTop(math::Vector2::Zero)
				, size(math::Vector2::Zero)
				, offset(math::Vector2::Zero)
				, duration(0.0f)
			{

			}
		};

	public:
		// ������
		Animation();
		// ���� ������
		Animation(const Animation& _anim);
		// ���� �Ҹ���
		// virtual Ű���带 �������ν� �ڼ� Ŭ�������� �θ� Ŭ�������� ������ �Ҹ��ڸ� ȣ���ϸ鼭
		// ������ Ŭ������ ������ ���� ���� ������ ���������ش�.
		virtual ~Animation();

		// �ʱ�ȭ�� ���� Initialize �Լ�
		void Initialize();
		// �ִϸ��̼��� ����� ���õ� ������ ó�����ش�.
		void Update();
		// �ִϸ��̼��� �������� �׷��ش�.
		void Render(HDC _hdc);

		// �θ� Ŭ������ Resource�κ��� override(������)�� Load �Լ�.
		// ���� �ִϸ��̼� ��ü�� ���Ϸ� ������ ���ɼ��� ������
		// ������ ������� �ʱ� ������ �����ϰ� return S_FALSE ó��
		virtual HRESULT Load(const std::wstring& _path) { return S_FALSE; };

		// �ִϸ��̼��� �������ش�.
		// ���� ���
		// name : �ִϸ��̼��� �̸�
		// Texture : ��Ʋ�� �ؽ�ó
		// leftTop : �� �������� ������ �»�� ��ġ
		// size : �� �������� ũ��
		// spriteLength : ��Ʋ�� �ؽ�ó���� ������ �������� ����
		// duration : �� �����Ӵ� ���� �ð�
		void Create(const std::wstring& _name, class Texture* _texture
					, math::Vector2 _leftTop, math::Vector2 _size, math::Vector2 _Interval, math::Vector2 _offset
					, UINT _spriteLength, float _duration);

		// ����� ���õ� ������ ���� �ʱ�ȭ���ش�. ��, �ִϸ��̼��� ����Ǳ� ������
		// �ǵ��� ���ٴ� ���̴�.
		void Reset();

		// �ִϸ��̼��� ����� �Ϸ�Ǿ������� ��ȯ�ϴ� getter �Լ�
		bool IsComplete() { return mbComplete; }
		// �ڽ��� �����ϰ� �ִ� �ִϸ����͸� �������ش�. ���� ������Ʈ�� ������Ʈ ��
		// Transform�� �����ؼ� ���� ��ġ�� �˾Ƴ��� �̿� ������ �޾Ƽ� �׷��� ��ġ��
		// ������ �� �ֱ� ������ �� �ִϸ��̼��� ������ �ִ� �ִϸ����͸� �������ش�.
		void SetAnimator(Animator* _animator) { mAnimator = _animator; }

		// private ���� ������ �� �ξ��ٸ� �Ʒ��� ������ �ܺο��� ������ �� ���ٴ� ���̴�.
	private:
		// �ش� �ִϸ��̼��� �����ϰ� �ִ� �ִϸ����� ��ü�� ����Ų��.
		Animator* mAnimator;
		// �� �ִϸ��̼��� render�� ��, �����Ͽ� �׷��� ��Ʋ�� �ؽ�ó
		Texture* mTexture;

		// �� ������ ������ ���� �迭�� �����Ѵ�.
		std::vector<Sprite> mSpriteSheet;
		// ���� ������ ��ȣ
		int mIndex;
		// ���� ���������� �ǰ� �� �� ����� �ð�
		float mTime;
		// �ִϸ��̼��� ��� �Ϸ� ����
		bool mbComplete;
	};

}
