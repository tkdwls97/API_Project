#pragma once
#include "exMonsters.h"

namespace ex
{

	class MushMom : public Monsters
	{
	public:
		MushMom();
		virtual ~MushMom();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* _other) override;
		virtual void OnCollisionStay(Collider* _other) override;
		virtual void OnCollisionExit(Collider* _other) override;

		void SetMoveDelay(float _delay) { mMoveDelay = _delay; }
		float GetMoveDelay() { return mMoveDelay; }

		void Idle();
		void Move();
		void Attack();
		void Chase();
		void Hit();
		void Dead();

	private:
	};

}