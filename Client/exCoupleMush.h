#pragma once
#include "exMonsters.h"

namespace ex
{

	class CoupleMush : public Monsters
	{
	public:
		CoupleMush();
		virtual ~CoupleMush();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void Idle();
		void Move();
		void Attack();
		void Chase();
		void Hit();
		void Dead();

	private:	
		float mIdleDelay;
		float mMoveDelay;
	};
}
