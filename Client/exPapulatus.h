#pragma once
#include "exMonsters.h"

namespace ex
{

	class Papulatus : public Monsters
	{
	public:
		Papulatus();
		virtual ~Papulatus();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

	private:

	};

}
