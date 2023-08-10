#pragma once
#include "exMonsters.h"

namespace ex
{

	class OrangeMush : public Monsters
	{
	public:
		OrangeMush();
		virtual ~OrangeMush();

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