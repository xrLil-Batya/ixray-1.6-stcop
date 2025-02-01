#include "StdAfx.h"
#include "pch_script.h"
#include "chimera_cs.h"

using namespace luabind;

#pragma optimize("s",on)
void CChimeraCS::script_register(lua_State* L)
{
	module(L)
		[
			class_<CChimeraCS, CGameObject>("CChimeraCS")
			.def(constructor<>())
		];
}