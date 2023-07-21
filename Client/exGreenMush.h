#pragma once
#include "exMonsters.h"

namespace ex
{

	class GreenMush : public Monsters
	{
	public:
		GreenMush();
		virtual ~GreenMush();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC _hdc) override;

	
	private:

	};

}
