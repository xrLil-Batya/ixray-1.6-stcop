#include "pch_script.h"
#include "bloodsucker.h"

using namespace luabind;

#pragma optimize("s",on)
void CBloodsuckerSoC::script_register(lua_State* L)
{
	module(L)
		[
			class_<CBloodsuckerSoC, CGameObject>("CBloodsuckerSoC")
			.def(constructor<>())
		];
}