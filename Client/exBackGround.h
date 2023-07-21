#pragma once
#include "exGameObject.h"

namespace ex
{

	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;


	private:

	};

}
