#include "StdAfx.h"
#include "chimera_cs.h"
#include "chimera_cs_state_hunting.h"

#include "chimera_cs_state_hunting_move_to_cover.h"
#include "chimera_cs_state_hunting_come_out.h"

CStateChimeraCSHunting::CStateChimeraCSHunting(CChimeraCS *obj) : inherited(obj)
{
	add_state(eStateMoveToCover,	new CStateChimeraCSHuntingMoveToCover	(obj));
	add_state(eStateComeOut,		new CStateChimeraCSHuntingComeOut		(obj));
}

bool CStateChimeraCSHunting::check_start_conditions()
{
	return true;
}

bool CStateChimeraCSHunting::check_completion()
{
	return false;
}

void CStateChimeraCSHunting::reselect_state()
{
	if (prev_substate == u32(-1))					select_state(eStateMoveToCover);
	else if (prev_substate == eStateMoveToCover)	select_state(eStateComeOut);
	else											select_state(eStateMoveToCover);
}
