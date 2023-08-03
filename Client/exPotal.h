#pragma once
#include "exGameObject.h"


namespace ex
{
	class Transform;

	class Potal : public GameObject
	{
	public:
		Potal();
		virtual ~Potal();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
	
	private:
		
	};

}
