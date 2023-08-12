#pragma once

#include <vector>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <assert.h>
#include <filesystem>
#include <bitset>

#include "framework.h"
#include "exMath.h"

#pragma comment(lib, "Msimg32.lib")

namespace ex::enums
{
	enum class eLayerType
	{
		Background,
		Floor,
		Wall,
		Rope,
		Potal,
		Monster,
		Player,
		PlayerFloor,
		Effect,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Collider,
		Rigidbody,
		End,
	};
	
	enum class eMoveDir
	{
		Right,
		Left,
		End,
	};

}

 

