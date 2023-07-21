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
		//f(��) = m(����)a ���ӵ�
	
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ������� �� �ӵ��� ���´�
		mVelocity += mAccelation * Time::GetDeltaTime();

		if (!(mVelocity == math::Vector2::Zero))
		{

			// �ӵ��� �ݴ� �������� ������ ����
			math::Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���

			if (mVelocity.Length() < friction.Length())
			{
				// ����
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