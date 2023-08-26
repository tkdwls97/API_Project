#include "exLevel.h"
#include "exPlayer.h"
#include "exInput.h" 
#include "exTime.h"
#include "exResourceManager.h"
#include "exTexture.h"
#include "exObject.h"
#include "exCollisionManager.h"
#include "exSceneManager.h"
#include "exSpriteRenderer.h"
// Component
#include "exTransform.h"
#include "exAnimator.h"
#include "exCollider.h"


namespace ex
{
	Level::Level()
		: mLevelArr{}

	{

		mLevelArr[0] = ResourceManager::Load<Texture>(L"LevelNum_0"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_0.bmp");
		mAnimator->CreateAnimation(L"LevelNum_0", mLevelArr[0], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[1] = ResourceManager::Load<Texture>(L"LevelNum_1"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_1.bmp");
		mAnimator->CreateAnimation(L"LevelNum_1", mLevelArr[1], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[2] = ResourceManager::Load<Texture>(L"LevelNum_2"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_2.bmp");
		mAnimator->CreateAnimation(L"LevelNum_2", mLevelArr[2], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[3] = ResourceManager::Load<Texture>(L"LevelNum_3"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_3.bmp");
		mAnimator->CreateAnimation(L"LevelNum_3", mLevelArr[3], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[4] = ResourceManager::Load<Texture>(L"LevelNum_4"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_4.bmp");
		mAnimator->CreateAnimation(L"LevelNum_4", mLevelArr[4], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[5] = ResourceManager::Load<Texture>(L"LevelNum_5"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_5.bmp");
		mAnimator->CreateAnimation(L"LevelNum_5", mLevelArr[5], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[6] = ResourceManager::Load<Texture>(L"LevelNum_6"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_6.bmp");
		mAnimator->CreateAnimation(L"LevelNum_6", mLevelArr[6], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[7] = ResourceManager::Load<Texture>(L"LevelNum_7"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_7.bmp");
		mAnimator->CreateAnimation(L"LevelNum_7", mLevelArr[7], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[8] = ResourceManager::Load<Texture>(L"LevelNum_8"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_8.bmp");
		mAnimator->CreateAnimation(L"LevelNum_8", mLevelArr[8], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);

		mLevelArr[9] = ResourceManager::Load<Texture>(L"LevelNum_9"
			, L"..\\Resources\\Maple\\Image\\UI\\LevelNum\\LevelNum_9.bmp");
		mAnimator->CreateAnimation(L"LevelNum_9", mLevelArr[9], math::Vector2(0.0f, 0.0f), math::Vector2(10.0f, 12.0f)
			, math::Vector2(10.0f, 12.0f), 1, math::Vector2(0.0f, 0.0f), 0.4f);
		mAnimator->SetAffectedCamera(false);
	}

	Level::~Level()
	{
	}

	void Level::Initialize()
	{
	}

	void Level::Update()
	{
		//PlayLevelAnimation();
		UI::Update();
	}

	void Level::Render(HDC _hdc)
	{
		UI::Render(_hdc);
	}

	void Level::OnCollisionEnter(Collider* _other)
	{
	}

	void Level::OnCollisionStay(Collider* _other)
	{
	}

	void Level::OnCollisionExit(Collider* _other)
	{
	}
	void Level::PlayLevelAnimation(Animator* _animator)
	{
		Player* player = SceneManager::GetPlayer();
		int level = player->GetInfo()->mLevel;

		std::string numStr = std::to_string(level);
		int len = static_cast<int>(numStr.length());

		int measure = 100;

		for (int i = 0; i < len; i++)
		{
			int result = level / measure;

			switch (result)
			{
			case 0:
				_animator->PlayAnimation(L"LevelNum_0", false);
				break;
			case 1:
				_animator->PlayAnimation(L"LevelNum_1", false);
				break;
			case 2:
				_animator->PlayAnimation(L"LevelNum_2", false);
				break;
			case 3:
				_animator->PlayAnimation(L"LevelNum_3", false);
				break;
			case 4:
				_animator->PlayAnimation(L"LevelNum_4", false);
				break;
			case 5:
				_animator->PlayAnimation(L"LevelNum_5", false);
				break;
			case 6:
				_animator->PlayAnimation(L"LevelNum_6", false);
				break;
			case 7:
				_animator->PlayAnimation(L"LevelNum_7", false);
				break;
			case 8:
				_animator->PlayAnimation(L"LevelNum_8", false);
				break;
			case 9:
				_animator->PlayAnimation(L"LevelNum_9", false);
				break;
			default:
				break;
			}

			mTransform->SetPosition(math::Vector2(630.0f, 360.0f));
			level -= result * measure;
			measure /= 10;
		}
	}
}
