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
#include <cstdio>


#include "framework.h"
#include "exMath.h"

#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace ex::enums
{
	enum class eLayerType
	{
		Background,
		Floor,
		Wall,
		Rope,
		NPC,
		Monster,
		Potal,
		Player,
		PlayerAttack,
		Effect,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animation,
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

 

