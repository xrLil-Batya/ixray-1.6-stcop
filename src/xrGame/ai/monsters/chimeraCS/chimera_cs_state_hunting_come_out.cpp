#include "StdAfx.h"
#include "chimera_cs.h"
#include "chimera_cs_state_hunting.h"
#include "chimera_cs_state_hunting_come_out.h"

CStateChimeraCSHuntingComeOut::CStateChimeraCSHuntingComeOut(CChimeraCS*obj) : inherited(obj)
{
}

bool CStateChimeraCSHuntingComeOut::check_start_conditions()
{
	return true;
}

bool CStateChimeraCSHuntingComeOut::check_completion()
{
	return false;
}

void CStateChimeraCSHuntingComeOut::reselect_state()
{
	if (prev_substate == u32(-1))					select_state(eStateMoveToCover);
	else if (prev_substate == eStateMoveToCover)	select_state(eStateComeOut);
	else											select_state(eStateMoveToCover);
}