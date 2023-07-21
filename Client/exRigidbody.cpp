#include "exRigidbody.h"
#include "exTime.h"
#include "exGameObject.h"
#include "exTransform.h"

namespace ex
{
	Rigidbody::Rigidbody()
		: Component(enums::eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(10.0f)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		//f(힘) = m(질량)a 가속도
	
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해줘야 총 속도가 나온다
		mVelocity += mAccelation * Time::GetDeltaTime();

		if (!(mVelocity == math::Vector2::Zero))
		{

			// 속도에 반대 방향으로 마찰력 적용
			math::Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();

			// 마찰력으로 의한 속도 감소량이 현재 속도보다 큰 경우

			if (mVelocity.Length() < friction.Length())
			{
				// 멈춰
				mVelocity = math::Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}


		Transform* tr = GetOwner()->GetComponent<Transform>();
		math::Vector2 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::GetDeltaTime();
		tr->SetPosition(pos);
		mForce.Clear();
	}

	void Rigidbody::Render(HDC _hdc)
	{
	}

}